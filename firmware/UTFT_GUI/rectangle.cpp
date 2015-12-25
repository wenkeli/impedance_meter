/*
 * rectangle.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: consciousness
 */

#include "UTFTGUIIncludes/elements/rectangle.h"

Rectangle::Rectangle()
{
	setParams(0, 0, 0, 0, VGA_BLACK);
}

Rectangle::Rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t lineColor)
{
	setParams(x, y, w, h, lineColor);
}

Rectangle::~Rectangle()
{
}

void Rectangle::init(UTFT *screen)
{
	this->screen=screen;
}

void Rectangle::init(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t lineColor, UTFT *screen)
{
	setParams(x, y, w, h, lineColor);
	init(screen);
}

void Rectangle::setParams(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t lineColor)
{
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;

	this->enabled=false;

	this->lineColor=lineColor;
}

void Rectangle::draw()
{
	if(!enabled)
	{
		return;
	}
	screen->setColor(lineColor);
	screen->drawRect(x, y, x+w, y+h);
}

void Rectangle::enable()
{
	enabled=true;
}

void Rectangle::disable()
{
	enabled=false;
}
