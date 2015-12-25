/*
 * hardware.h
 *
 *  Created on: Jun 16, 2014
 *      Author: consciousness
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <libmaple/gpio.h>
#include <libmaple/i2c.h>

#include <wirish/HardwareSerial.h>
#include <wirish/wirish.h>

#include <UTFT.h>
#include <UTouch.h>


#include "channelmap.h"
#include "currentsrc.h"
#include "impedancemeasure.h"

extern CurrentSrc curSrc;
extern ImpedanceMeasure impedance;
extern UTFT screen;
extern UTouch tPanel;

void initHardware();

#endif /* HARDWARE_H_ */
