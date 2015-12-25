/*
 * rectangle.h
 *
 *  Created on: Jun 15, 2014
 *      Author: consciousness
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <UTFT.h>
#include <stdint.h>

class Rectangle
{
public:
	Rectangle();
	Rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t lineColor);
	virtual ~Rectangle();

	virtual void init(UTFT *screen);
	virtual void init(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t lineColor, UTFT *screen);
	virtual void setParams(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
			uint16_t lineColor);

	virtual void enable();
	virtual void disable();

	virtual void draw();

private:
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;

	bool enabled;

	uint16_t lineColor;
	UTFT *screen;
};


#endif /* RECTANGLE_H_ */
