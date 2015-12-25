/*
 * basepage.cpp
 *
 *  Created on: Jun 7, 2014
 *      Author: consciousness
 */

#include "UTFTGUIIncludes/containers/basepage.h"

BasePage::BasePage(Button **buttons, uint16_t numButtons,
		TextDisplay **displays, uint16_t numDisplays,
		Rectangle **rectangles, uint16_t numRects,
		uint16_t backgroundColor)
{
	this->buttons=buttons;
	this->numButtons=numButtons;

	this->displays=displays;
	this->numDisplays=numDisplays;

	bgColor=backgroundColor;
}

BasePage::~BasePage()
{

}

void BasePage::init(UTFT *screen)
{
	this->screen=screen;

	for(int i=0; i<numButtons; i++)
	{
		buttons[i]->init(screen);
	}
	for(int i=0; i<numRects; i++)
	{
		rectangles[i]->init(screen);
	}
	for(int i=0; i<numDisplays; i++)
	{
		displays[i]->init(screen);
	}
}

void BasePage::checkPageClicked(uint16_t x, uint16_t y)
{
	for(int i=0; i<numButtons; i++)
	{
		buttons[i]->checkClicked(x, y);
	}
}

void BasePage::drawPage()
{
	screen->fillScr(bgColor);

	for(int i=0; i<numButtons; i++)
	{
		buttons[i]->enable();
		buttons[i]->draw();
	}

	for(int i=0; i<numRects; i++)
	{
		rectangles[i]->enable();
		rectangles[i]->draw();
	}

	for(int i=0; i<numDisplays; i++)
	{
		displays[i]->enable();
		displays[i]->draw();
	}
}

void BasePage::disable()
{
	screen->clrScr();
	for(int i=0; i<numButtons; i++)
	{
		buttons[i]->disable();
	}

	for(int i=0; i<numRects; i++)
	{
		rectangles[i]->disable();
	}

	for(int i=0; i<numDisplays; i++)
	{
		displays[i]->disable();
	}
}


