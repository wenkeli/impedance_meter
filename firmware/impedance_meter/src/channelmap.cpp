#include "../include/channelmap.h"

GPIOPin disablePin(GPIOE, 6);
GPIOPin sourcePin(GPIOE, 0);
GPIOPin led0Pin(GPIOB, 0);
GPIOPin led1Pin(GPIOB, 1);


//TetrodeCHs tetrodes[8]={
//		{{{X8X16BCH, 11}, {X8X16TCH, 1}, {X8X16TCH, 0}, {X8X16TCH, 2}}},
//		{{{X8X16BCH, 10}, {X8X16TCH, 3}, {X8X16TCH, 4}, {X8X16TCH, 5}}},
//		{{{X8X16TCH, 7}, {X8X16TCH, 9}, {X8X16TCH, 6}, {X8X16TCH, 8}}},
//		{{{X8X16TCH, 10}, {X8X16TCH, 12}, {X8X16TCH, 11}, {X8X16BCH, 5}}},
//		{{{X8X16TCH, 14}, {X8X16TCH, 13}, {X8X16TCH, 15}, {X8X16BCH, 4}}},
//		{{{X8X16BCH, 0}, {X8X16BCH, 1}, {X8X16BCH, 2}, {X8X16BCH, 3}}},
//		{{{X8X16BCH, 6}, {X8X16BCH, 7}, {X8X16BCH, 8}, {X8X16BCH, 9}}},
//		{{{X8X16BCH, 12}, {X8X16BCH, 13}, {X8X16BCH, 14}, {X8X16BCH, 15}}}
//};

Channel allCHs[36]={
		{X8EXTCH, 0, 0, 0}, {X8CALCH, 0, 0, 0}, {X8REF2CH, 0, 0, 0}, {X8REF1CH, 0, 0, 0},
		{X8X16BCH, 11, 0, 0}, {X8X16TCH, 1, 0, 0}, {X8X16TCH, 0, 0, 0}, {X8X16TCH, 2, 0, 0},
		{X8X16BCH, 10, 0, 0}, {X8X16TCH, 3, 0, 0}, {X8X16TCH, 4, 0, 0}, {X8X16TCH, 5, 0, 0},
		{X8X16TCH, 7, 0, 0}, {X8X16TCH, 9, 0, 0}, {X8X16TCH, 6, 0, 0}, {X8X16TCH, 8, 0, 0},
		{X8X16TCH, 10, 0, 0}, {X8X16TCH, 12, 0, 0}, {X8X16TCH, 11, 0, 0}, {X8X16BCH, 5, 0, 0},
		{X8X16TCH, 14, 0, 0}, {X8X16TCH, 13, 0, 0}, {X8X16TCH, 15, 0, 0}, {X8X16BCH, 4, 0, 0},
		{X8X16BCH, 0, 0, 0}, {X8X16BCH, 1, 0, 0}, {X8X16BCH, 2, 0, 0}, {X8X16BCH, 3, 0, 0},
		{X8X16BCH, 6, 0, 0}, {X8X16BCH, 7, 0, 0}, {X8X16BCH, 8, 0, 0}, {X8X16BCH, 9, 0, 0},
		{X8X16BCH, 12, 0, 0}, {X8X16BCH, 13, 0, 0}, {X8X16BCH, 14, 0, 0}, {X8X16BCH, 15, 0, 0}
};

Channel *extCH=&allCHs[0];
Channel *calCH=&allCHs[1];
Channel *ref2CH=&allCHs[2];
Channel *ref1CH=&allCHs[3];

Tetrode tetrodes[8]={
		{{&allCHs[4], &allCHs[5], &allCHs[6], &allCHs[7]}},
		{{&allCHs[8], &allCHs[9], &allCHs[10], &allCHs[11]}},
		{{&allCHs[12], &allCHs[13], &allCHs[14], &allCHs[15]}},
		{{&allCHs[16], &allCHs[17], &allCHs[18], &allCHs[19]}},
		{{&allCHs[20], &allCHs[21], &allCHs[22], &allCHs[23]}},
		{{&allCHs[24], &allCHs[25], &allCHs[26], &allCHs[27]}},
		{{&allCHs[28], &allCHs[29], &allCHs[30], &allCHs[31]}},
		{{&allCHs[32], &allCHs[33], &allCHs[34], &allCHs[35]}}
};

ChannelMap resistorMap(GPIOE, 0x0030, 0x0003, 4);
ChannelMap x8Map(GPIOE, 0x000E, 0x0007, 1);
ChannelMap x16Map(GPIOB, 0xF000, 0x000F, 12);


GPIOPin::GPIOPin(gpio_dev *port, uint8 pinN)
{
	this->port=port;
	this->pinN=pinN;
}
void GPIOPin::init()
{
	gpio_set_mode(port, pinN, GPIO_OUTPUT_PP);
}
void GPIOPin::writePin(uint8 bit)
{
	gpio_write_bit(port, pinN, bit);
	delay(1);
}
void GPIOPin::togglePin()
{
	gpio_toggle_bit(port, pinN);
	delay(1);
}


void Channel::activateCH()
{
	x8Map.selectChannel(x8CH);
	x16Map.selectChannel(x16CH);
	delay(10);
}

ChannelMap::ChannelMap(gpio_dev *port, uint16 portMask, uint16 chMask, uint8 chShift)
{
	this->port=port;
	this->portMask=~portMask;
	this->chMask=chMask;
	this->chShift=chShift;
}

void ChannelMap::init()
{
	for(int i=0; i<16; i++)
	{
		if(((~portMask) & (0x01<<i))>0)
		{
			gpio_set_mode(port, i, GPIO_OUTPUT_PP);
		}
	}
}

void ChannelMap::selectChannel(uint16 ch)
{
	ch=ch & chMask;

	port->regs->ODR=(port->regs->ODR & portMask) | (ch<<chShift);
	delay(1);
}


void initChannels()
{
	gpio_set_mode(GPIOE, 0, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 1, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 2, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 3, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 4, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 5, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 6, GPIO_OUTPUT_PP);

	gpio_set_mode(GPIOB, 12, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOB, 13, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOB, 14, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOB, 15, GPIO_OUTPUT_PP);

	sourcePin.init();
	sourcePin.writePin(0);

	disablePin.init();
	disablePin.writePin(1);

	extCH->activateCH();

	led0Pin.init();
	led1Pin.init();
}
