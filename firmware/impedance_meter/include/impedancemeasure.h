/*
 * impedancemeasure.h
 *
 *  Created on: Jun 2, 2014
 *      Author: consciousness
 */

#ifndef IMPEDANCEMEASURE_H_
#define IMPEDANCEMEASURE_H_

#include <libmaple/i2c.h>
#include <wirish/wirish.h>
#include <wirish/HardwareSerial.h>
#include <libmaple/gpio.h>
#include <math.h>
#include "channelmap.h"

struct AD5933Reg
{
	uint8 startAddr;
	uint8 dataLen;

	uint8 addr[3];
	uint8 dataR[3];
	uint8 dataW[3];

	void initialize(uint8 startAddr, uint8 len);
};

struct CalData
{
	double resistorVal;
	uint16 calCh;
	double calGainF;
	double minMeasureVal;
};
class ImpedanceMeasure
{
public:
	ImpedanceMeasure(ChannelMap *resistorMap, ChannelMap *x8Map);
	void init();

	double measureImpedance();

	void outputFreq();

private:
	void writeRegister(AD5933Reg *reg);
	void readRegister(AD5933Reg *reg);

	void setFreq();
	void standby();
	void initFreq();
	void startFreqSweep();

	void powerDown();

	void measure();

	void runCalibration(CalData *cal);

	ChannelMap *resistorMap;
	ChannelMap *x8Map;
	i2c_msg msg;

	uint8 msgData[2];

	CalData cals[4];

	int16 rawReal;
	int16 rawImaginary;

	AD5933Reg ctrl;
	AD5933Reg startFreq;
	AD5933Reg freqInc;
	AD5933Reg numInc;
	AD5933Reg numSetCycle;
	AD5933Reg status;
	AD5933Reg tempData;
	AD5933Reg realData;
	AD5933Reg imaginaryData;
};



#endif /* IMPEDANCEMEASURE_H_ */
