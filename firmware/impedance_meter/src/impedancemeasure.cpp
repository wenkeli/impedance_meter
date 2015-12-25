/*
 * impedancemeasure.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: consciousness
 */

#include "../include/impedancemeasure.h"

#define BLOCKWRITE 0xA0
#define BLOCKREAD 0xA1
#define ADDRPTR 0xB0

#define STATHASTEMP 0x01
#define STATHASDATA 0x02
#define STATSWEEPDONE 0x04

void AD5933Reg::initialize(uint8 startAddr, uint8 len)
{
	this->startAddr=startAddr;
	this->dataLen=len;

	for(int i=0; i<len; i++)
	{
		addr[i]=startAddr+i;
		dataR[i]=0;
		dataW[i]=0;
	}
}

ImpedanceMeasure::ImpedanceMeasure(ChannelMap *resistorMap, ChannelMap *x8Map)
{
	this->resistorMap=resistorMap;
	this->x8Map=x8Map;

	msg.addr=0x0D;

	cals[0].resistorVal=3650.0;
	cals[0].calCh=R1KCH;
	cals[0].minMeasureVal=1000.0;

	cals[1].resistorVal=36500.0;
	cals[1].calCh=R10KCH;
	cals[1].minMeasureVal=10000.0;

	cals[2].resistorVal=365000.0;
	cals[2].calCh=R100KCH;
	cals[2].minMeasureVal=100000.0;

	cals[3].resistorVal=1500000.0;
	cals[3].calCh=R1MCH;
	cals[3].minMeasureVal=1000000.0;

	rawReal=0;
	rawImaginary=0;

	ctrl.initialize(0x80, 2);
	startFreq.initialize(0x82, 3);
	freqInc.initialize(0x85, 3);
	numInc.initialize(0x88, 2);
	numSetCycle.initialize(0x8A, 2);
	status.initialize(0x8F, 1);
	tempData.initialize(0x92, 2);
	realData.initialize(0x94, 2);
	imaginaryData.initialize(0x96, 2);
}

void ImpedanceMeasure::init()
{
	setFreq();

	sourcePin.writePin(0);
	disablePin.writePin(0);
	delay(10);

	for(int i=0; i<4; i++)
	{
		runCalibration(&cals[i]);
	}

	disablePin.writePin(1);
}

double ImpedanceMeasure::measureImpedance()
{
	double imp;
	double real;
	double imaginary;

	sourcePin.writePin(0);
	disablePin.writePin(0);
	delay(10);

	for(int i=0; i<4; i++)
	{
		resistorMap->selectChannel(cals[i].calCh);

		measure();
		real=rawReal;
		imaginary=rawImaginary;

		imp=1.0/(cals[i].calGainF*
				sqrt((double)(real*real)+(double)(imaginary*imaginary)));

		if(imp<cals[i].minMeasureVal*10.5)
		{
			break;
		}
	}
	disablePin.writePin(1);

	return imp;
}

void ImpedanceMeasure::runCalibration(CalData *cal)
{
	double real;
	double imaginary;

	calCH->activateCH();

	resistorMap->selectChannel(cal->calCh);
	delay(10);

//	Serial1.print(cal->resistorVal);
//	Serial1.print(" ");

	measure();

	real=rawReal;
	imaginary=rawImaginary;

	cal->calGainF=1.0/((double)(cal->resistorVal))/
			sqrt(real*real+imaginary*imaginary);

//	Serial1.println(cal->calGainF, 20);
}

void ImpedanceMeasure::writeRegister(AD5933Reg *reg)
{
	uint32 stat;
	msg.flags=0;
	msg.data=msgData;
	msg.length=2;
	for(int i=0; i<reg->dataLen; i++)
	{
		msgData[0]=reg->addr[i];
		msgData[1]=reg->dataW[i];

		stat=i2c_master_xfer(I2C2, &msg, 1, 1);

	}
}

void ImpedanceMeasure::readRegister(AD5933Reg *reg)
{
	uint32 stat;

	msg.flags=0;
	msg.data=msgData;
	msg.length=2;

	msgData[0]=ADDRPTR;
	msgData[1]=reg->startAddr;
	stat=i2c_master_xfer(I2C2, &msg, 1, 1);
//	Serial1.println(stat);

	msgData[0]=BLOCKREAD;
	msgData[1]=reg->dataLen;
	stat=i2c_master_xfer(I2C2, &msg, 1, 1);
//	Serial1.println(stat);

	msg.flags=I2C_MSG_READ;
	msg.data=reg->dataR;
	msg.length=reg->dataLen;
	stat=i2c_master_xfer(I2C2, &msg, 1, 1);
//	Serial1.println(stat);
}

void ImpedanceMeasure::setFreq()
{
	uint32 freqData;
	freqData=(1000.0/(1843200.0/16))*(0x01<<27); //16000000
	startFreq.dataW[0]=(freqData & 0x00FF0000)>>16;
	startFreq.dataW[1]=(freqData & 0x0000FF00)>>8;
	startFreq.dataW[2]=freqData & 0x000000FF;

	numInc.dataW[0]=0;
	numInc.dataW[1]=1;

	freqInc.dataW[0]=0;
	freqInc.dataW[1]=0;
	freqInc.dataW[2]=0;

	numSetCycle.dataW[0]=0x00;
	numSetCycle.dataW[1]=0x64;

	writeRegister(&startFreq);
	writeRegister(&numInc);
	writeRegister(&freqInc);
	writeRegister(&numSetCycle);
}

void ImpedanceMeasure::outputFreq()
{
	gpio_write_bit(sourcePin.port, sourcePin.pinN, 0);
	standby();
	initFreq();
}

void ImpedanceMeasure::standby()
{
	ctrl.dataW[0]=0xB4;
	ctrl.dataW[1]=0x18;

	writeRegister(&ctrl);

	delay(10);
}

void ImpedanceMeasure::startFreqSweep()
{
	ctrl.dataW[0]=0x24;
	ctrl.dataW[1]=0x08;

	writeRegister(&ctrl);

	delay(150);
}

void ImpedanceMeasure::initFreq()
{
	ctrl.dataW[0]=0x14;
	ctrl.dataW[1]=0x08;

	writeRegister(&ctrl);
}

void ImpedanceMeasure::powerDown()
{
	ctrl.dataW[0]=0xA4;
	ctrl.dataW[1]=0x08;
	writeRegister(&ctrl);
}

void ImpedanceMeasure::measure()
{
	standby();
	initFreq();
	startFreqSweep();

	rawReal=0;
	rawImaginary=0;

	while(1)
	{
		readRegister(&status);
		if((status.dataR[0] & STATHASDATA)>0)
		{
			break;
		}
		delay(1);
	}

	for(int i=0; i<3; i++)
	{
		realData.dataR[i]=0;
		imaginaryData.dataR[i]=0;
	}
	readRegister(&realData);
	readRegister(&imaginaryData);

	rawReal=realData.dataR[0]<<8;
	rawReal=rawReal | realData.dataR[1];
	rawImaginary=imaginaryData.dataR[0]<<8;
	rawImaginary=rawImaginary | imaginaryData.dataR[1];
//	Serial1.print(rawReal);
//	Serial1.print(" ");
//	Serial1.println(rawImaginary);
}
