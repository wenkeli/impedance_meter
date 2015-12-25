/*
 * button.h
 *
 *  Created on: Jun 7, 2014
 *      Author: consciousness
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../actions/baseaction.h"
#include <stdint.h>
#include <string>
#include <UTFT.h>
#include "textdisplay.h"

class Button
{
public:
	Button();
	Button(BaseAction *act, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t color, uint16_t toggleColor,
			uint16_t txtColor, uint16_t nChars, uint8_t *font,
			uint8_t labelType, const char *label, double num, uint32 base,
			bool togglable);
	virtual ~Button();

	virtual void init(UTFT *screen);
	virtual void init(BaseAction *act, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t color, uint16_t toggleColor,
			uint16_t txtColor, uint16_t nChars, uint8_t *font,
			uint8_t labelType, const char *label, double num, uint32 base,
			bool togglable, UTFT *screen);

	void setParams(BaseAction *act, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t color, uint16_t toggleColor,
			uint16_t txtColor, uint16_t nChars, uint8_t *font,
			uint8_t labelType, const char *label, double num, uint32 base,
			bool togglable);

	virtual void checkClicked(uint16_t pressX, uint16_t pressY);
	virtual void click();

	virtual void flashOn(uint16 flashC);
	virtual void flashOff();

	virtual void draw();
	virtual void enable();
	virtual void disable();
	virtual void setLabel(const char *st);
	virtual void setLabel(double num);

	TextDisplay *getLabelDisp();

private:
	void drawButton(uint16 color);
	uint16_t x;
	uint16_t y;
	uint16_t tX;
	uint16_t tY;
	uint16_t w;
	uint16_t h;

	BaseAction *action;

	TextDisplay label;

	uint16_t txtColor;
	uint16_t numChars;
	uint8_t *font;

	uint8_t labelType;
	std::string labelStr;
	double labelNum;
	uint32 labelBase;

	uint16_t color;
	uint16_t toggleColor;
	UTFT *screen;

	bool enabled;

	bool togglable;
	bool toggled;
	uint16_t curColor;

};



#endif /* BUTTON_H_ */
