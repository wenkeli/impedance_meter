#ifndef CURRENTSRC_H_
#define CURRENTSRC_H_

#include <libmaple/i2c.h>
#include <wirish/wirish.h>
#include <libmaple/gpio.h>
#include <stdint.h>
#include "channelmap.h"

class CurrentSrc
{
public:
	CurrentSrc();

	void setCurrent(uint32 uA);
	void setTime(uint32 ms);
	uint32 *getCurrentPt();
	uint32 *getTimePt();
	uint32 getCurrent();
	uint32 getTime();
	int32 passCurrent(uint32 uA, uint32 ms);
	int32 passCurrent();
private:
	uint32 calcResist(uint32 uA);

	uint8 dataW[2];
	uint8 dataR[1];

	i2c_msg msg;

	float dPotRKStep;
	uint32 uA;
	uint32 ms;
};

#endif
