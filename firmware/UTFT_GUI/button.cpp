/*
 * button.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: consciousness
 */

#include "UTFTGUIIncludes/elements/button.h"

using namespace std;

Button::Button()
{
	setParams(0, 0, 0, 0, 0, VGA_BLACK, VGA_BLACK, VGA_BLACK, 0, SmallFont,
			0, "", 0, 1, false);
}

Button::Button(BaseAction *act, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t color, uint16_t toggleColor,
			uint16_t txtColor, uint16_t nChars, uint8_t *font,
			uint8_t labelType, const char *label, double num, uint32 base,
			bool togglable)
{
	setParams(act, x, y, w, h, color, toggleColor,
			txtColor, nChars, font, labelType, label, num, base, togglable);
}

Button::~Button()
{
}

void Button::setParams(BaseAction *act, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t color, uint16_t toggleColor,
			uint16_t txtColor, uint16_t nChars, uint8_t *font,
			uint8_t labelType, const char *label, double num, uint32 base,
			bool togglable)
{
	action=act;
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;

	this->tX=x;
	this->tY=y;

	this->color=color;
	this->toggleColor=toggleColor;
	curColor=color;

	this->txtColor=txtColor;
	this->font=font;
	this->numChars=nChars;
	this->labelType=labelType;
	this->labelStr=label;
	this->labelNum=num;
	this->labelBase=base;

	enabled=false;

	toggled=false;
	this->togglable=togglable;
}


void Button::enable()
{
	enabled=true;
	label.enable();
}

void Button::disable()
{
	enabled=false;
	label.disable();
}

void Button::init(UTFT *screen)
{
	int labelW;
	int labelH;
	this->screen=screen;

	screen->setFont(font);
	labelW=screen->getFontXsize();
	labelH=screen->getFontYsize();

	labelW=numChars*labelW;

	tX=x+(w/2)-labelW/2;
	tY=y+(h/2)-labelH/2;

	label.init(tX, tY, txtColor, curColor, font,
			labelType, numChars, labelStr.c_str(), labelNum, labelBase, screen);
}

void Button::init(BaseAction *act, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t color, uint16_t toggleColor,
		uint16_t txtColor, uint16_t nChars, uint8_t *font,
		uint8_t labelType, const char *label, double num, uint32 base,
		bool togglable, UTFT *screen)
{
	setParams(act, x, y, w, h, color, toggleColor,
			txtColor, nChars, font, labelType,  label, num, base, togglable);
	init(screen);
}

void Button::checkClicked(uint16_t pressX, uint16_t pressY)
{
	if(!enabled)
	{
		return;
	}
	if(pressX>x && pressX<(x+w) && (pressY>y) && pressY<(y+h))
	{
		click();
	}
}

void Button::click()
{
	if(!enabled)
	{
		return;
	}
	if(togglable)
	{
		if(toggled)
		{
			curColor=color;
		}
		else
		{
			curColor=toggleColor;
		}
		toggled=!toggled;

		draw();
		action->run();
	}
	else
	{
		curColor=toggleColor;
		draw();
		action->run();
		delay(10);
		curColor=color;
		draw();
	}
}

void Button::draw()
{
	if(!enabled)
	{
		return;
	}
	drawButton(curColor);
}

void Button::drawButton(uint16 color)
{
	screen->setColor(color);
	screen->fillRoundRect(x, y, x+w, y+h);

	label.setTxtBGColor(color);
	label.draw();
}

void Button::flashOn(uint16 flashC)
{
	if(!enabled)
	{
		return;
	}
	drawButton(flashC);
}
void Button::flashOff()
{
	if(!enabled)
	{
		return;
	}
	drawButton(curColor);
}

void Button::setLabel(const char *st)
{
	labelStr=st;
	label.setStr(st);
	label.draw();
}

void Button::setLabel(double num)
{
	labelNum=num;
	label.setNum(num);
	label.draw();
}

TextDisplay *Button::getLabelDisp()
{
	return &label;
}
