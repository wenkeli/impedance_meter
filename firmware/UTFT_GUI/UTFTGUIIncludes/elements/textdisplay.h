/*
 * textdisplay.h
 *
 *  Created on: Jun 7, 2014
 *      Author: consciousness
 */

#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include <UTFT.h>
#include <stdint.h>
#include <string>

#define STRLABEL 0
#define INTLABEL 1
#define FLOATLABEL 2

class TextDisplay
{
public:
	TextDisplay();
	TextDisplay(uint16_t x, uint16_t y,
			uint16_t txtColor, uint16_t txtBGColor, uint8_t *font,
			uint8_t type, uint8_t nChars,
			const char *label, double num, uint32 base);
	virtual ~TextDisplay();

	virtual void init(UTFT *screen);
	virtual void init(uint16_t x, uint16_t y,
			uint16_t txtColor, uint16_t txtBGColor, uint8_t *font,
			uint8_t type, uint8_t nChars, const char *label,
			double num, uint32 base, UTFT *screen);

	void setParams(uint16_t x, uint16_t y,
			uint16_t txtColor, uint16_t txtBGColor, uint8_t *font,
			uint8_t type, uint8_t nChars,
			const char *label, double num, uint32 base);

	virtual void draw();

//	virtual void print(char *st, int relX, int relY);
//	virtual void printNumI(long int num, int relX, int relY, int length);
//	virtual void printNumF(double num, int relX, int relY, int dec);

	virtual void enable();
	virtual void disable();

	virtual void setTxtBGColor(uint16_t color);
	virtual void setTxtColor(uint16_t color);

	virtual void setStr(const char *str);
	virtual void setNum(double num);
	virtual void setBase(uint32 base);

//	UTFT *getScreen();
private:
	uint16_t x;
	uint16_t y;

	bool enabled;
	uint16_t txtColor;
	uint16_t txtBGColor;
	uint8_t *font;

	uint8_t type;
	uint8_t numChars;
	std::string str;
	double num;
	uint32 base;
	UTFT *screen;
};



#endif /* TEXTDISPLAY_H_ */
