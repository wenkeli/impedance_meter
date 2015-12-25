/*
 * page.h
 *
 *  Created on: Jun 7, 2014
 *      Author: consciousness
 */

#ifndef PAGE_H_
#define PAGE_H_

#include "../elements/button.h"
#include "../elements/textdisplay.h"
#include "../elements/rectangle.h"

#include <stdint.h>

#include <UTFT.h>


class BasePage
{
public:
	BasePage(Button **buttons, uint16_t numButtons,
			TextDisplay **displays, uint16_t numDisplays,
			Rectangle **rectangles, uint16_t numRects,
			uint16_t backgroundColor);
	virtual ~BasePage();

	virtual void init(UTFT *screen);

	virtual void checkPageClicked(uint16_t x, uint16_t y);
	virtual void drawPage();
	virtual void disable();

protected:
	uint16_t numButtons;
	Button **buttons;

	uint16_t numDisplays;
	TextDisplay **displays;

	uint16_t numRects;
	Rectangle **rectangles;

	uint16_t bgColor;

	UTFT *screen;
};

#endif /* PAGE_H_ */
