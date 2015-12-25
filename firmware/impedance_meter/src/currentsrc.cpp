#include "../include/currentsrc.h"

CurrentSrc::CurrentSrc()
{
	dataW[0]=0x00;

	msg.addr=0x2C;

	dPotRKStep=200.0/256;

	uA=0;
	ms=0;
}

void CurrentSrc::setCurrent(uint32 uA)
{
	this->uA=uA;
}
void CurrentSrc::setTime(uint32 ms)
{
	this->ms=ms;
}

uint32 CurrentSrc::getCurrent()
{
	return uA;
}

uint32 *CurrentSrc::getTimePt()
{
	return &ms;
}
uint32 *CurrentSrc::getCurrentPt()
{
	return &uA;
}

uint32 CurrentSrc::getTime()
{
	return ms;
}

int32 CurrentSrc::passCurrent(uint32 uA, uint32 ms)
{
	this->uA=uA;
	this->ms=ms;
	return passCurrent();
}

int32 CurrentSrc::passCurrent()
{
	int32 stat;

	if(uA==0)
	{
		return 0;
	}

	dataW[1]=calcResist(uA);
	msg.data=dataW;
	msg.flags=0;
	msg.length=2;
	stat=i2c_master_xfer(I2C2, &msg, 1, 1);

	sourcePin.writePin(1);
	disablePin.writePin(0);
	delay(ms);
	disablePin.writePin(1);
	sourcePin.writePin(0);

	return stat;
}

uint32 CurrentSrc::calcResist(uint32 uA)
{
	float rKOhm;
	uint8 dPotStep;

	rKOhm=64.0/uA*1.059;

	dPotStep=255-(uint8)((rKOhm-0.06)/dPotRKStep);

	return dPotStep;
}


