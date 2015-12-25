#ifndef CHANNELMAP_H_
#define CHANNELMAP_H_

#include <libmaple/gpio.h>
#include <wirish/wirish.h>
#include <stdint.h>

struct GPIOPin
{
	gpio_dev *port;
	uint8 pinN;

	GPIOPin(gpio_dev *port, uint8 pinN);
	void init();

	void writePin(uint8 bit);
	void togglePin();
};

struct Channel
{
	uint8 x8CH;
	uint8 x16CH;

	uint8  selected;
	double impedance;
	void activateCH();
};

extern Channel allCHs[36];

//struct TetrodeCHs
//{
//	Channel channels[4];
//};

struct Tetrode
{
	Channel* channels[4];
};

extern GPIOPin disablePin;
extern GPIOPin sourcePin;

extern GPIOPin led0Pin;
extern GPIOPin led1Pin;

extern Channel allCHs[36];

extern Channel *extCH;
extern Channel *calCH;
extern Channel *ref2CH;
extern Channel *ref1CH;

extern Tetrode tetrodes[8];

#define R1KCH 0
#define R10KCH 1
#define R100KCH 2
#define R1MCH 3

#define X8EXTCH 0
#define X8CALCH 2
#define X8REF2CH 3
#define X8REF1CH 4
#define X8X16BCH 5
#define X8X16TCH 7

#define X16CH(ch) ch

class ChannelMap
{
public:
	ChannelMap(gpio_dev *port, uint16 portMask, uint16 chMask, uint8 chShift);
	void init();

	void selectChannel(uint16 ch);

private:
	gpio_dev *port;
	uint16 portMask;
	uint16 chMask;
	uint8 chShift;
};

void initChannels();

extern ChannelMap resistorMap;
extern ChannelMap x8Map;
extern ChannelMap x16Map;

#endif
