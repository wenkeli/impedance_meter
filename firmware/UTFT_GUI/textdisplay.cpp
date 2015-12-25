/*
 * textdisplay.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: consciousness
 */

#include "UTFTGUIIncludes/elements/textdisplay.h"

using namespace std;

TextDisplay::TextDisplay()
{
	setParams(0, 0, VGA_BLACK, VGA_BLACK, SmallFont,
			0, 0, "", 0, 1);
}

TextDisplay::TextDisplay(uint16_t x, uint16_t y,
		uint16_t txtColor, uint16_t txtBGColor, uint8_t *font,
		uint8_t type, uint8_t nChars,
		const char *label, double num, uint32 base)
{
	setParams(x, y, txtColor, txtBGColor, font,
			type, nChars, label, num, base);
}

TextDisplay::~TextDisplay()
{
}

void TextDisplay::init(UTFT *screen)
{
	this->screen=screen;
}

void TextDisplay::init(uint16_t x, uint16_t y,
			uint16_t txtColor, uint16_t txtBGColor, uint8_t *font,
			uint8_t type, uint8_t nChars,
			const char *label, double num, uint32 base,
			UTFT *screen)
{
	setParams(x, y, txtColor, txtBGColor, font,
			type, nChars, label, num, base);
	init(screen);
}

void TextDisplay::setParams(uint16_t x, uint16_t y,
			uint16_t txtColor, uint16_t txtBGColor, uint8_t *font,
			uint8_t type, uint8_t nChars,
			const char *label, double num, uint32 base)
{
	this->x=x;
	this->y=y;

	this->txtBGColor=txtBGColor;
	this->txtColor=txtColor;

	this->font=font;
	this->type=type;
	this->numChars=nChars;
	this->str=label;
	this->base=base;
	this->num=num/base;

	this->enabled=false;
}

void TextDisplay::draw()
{
	int fontX;
	if(!enabled)
	{
		return;
	}
	screen->setBackColor(txtBGColor);
	screen->setColor(txtColor);
	screen->setFont(font);

	fontX=screen->getFontXsize();
	for(int i=0; i<numChars; i++)
	{
		screen->print(" ", fontX*i+x, y);
	}
	if(type==STRLABEL)
	{
		screen->print((char *)str.c_str(), x, y);
	}
	else if(type==INTLABEL)
	{
		screen->printNumI(num, x, y, numChars);
	}
	else
	{
		screen->printNumF(num, 1, x, y, '.', numChars, ' ');
	}
}

//void TextDisplay::print(char *st, int relX, int relY)
//{
//	if(!enabled)
//	{
//		return;
//	}
//
//	screen->setBackColor(txtBGColor);
//	screen->setColor(txtColor);
//	screen->setFont(font);
//	screen->print(st, x+relX, y+relY);
//}
//
//void TextDisplay::printNumI(long int num, int relX, int relY, int length)
//{
//	if(!enabled)
//	{
//		return;
//	}
//	screen->setBackColor(txtBGColor);
//	screen->setColor(txtColor);
//	screen->setFont(font);
//	screen->printNumI(num, x+relX, y+relY, length);
//}
//
//void TextDisplay::printNumF(double num, int relX, int relY, int dec)
//{
//	if(!enabled)
//	{
//		return;
//	}
//	screen->setBackColor(txtBGColor);
//	screen->setColor(txtColor);
//	screen->setFont(font);
//	screen->printNumF(num, dec, x+relX, y+relY);
//}

//UTFT *TextDisplay::getScreen()
//{
//	return screen;
//}

void TextDisplay::enable()
{
	enabled=true;
}
void TextDisplay::disable()
{
	enabled=false;
}

void TextDisplay::setTxtBGColor(uint16_t color)
{
	txtBGColor=color;
}
void TextDisplay::setTxtColor(uint16_t color)
{
	txtColor=color;
}

void TextDisplay::setStr(const char *str)
{
	this->str=str;
}

void TextDisplay::setNum(double num)
{
	this->num=num/base;
}

void TextDisplay::setBase(uint32 base)
{
	num=num*this->base;
	this->base=base;
	num=num/this->base;
}
