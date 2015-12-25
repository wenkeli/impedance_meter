#include <UTFT.h>
#include <UTouch.h>

#define TOUCH_ORIENTATION  PORTRAIT


extern uint8_t SmallFont[];

UTFT myGLCD(SSD1289, 48+11, 48+5, 48+7, 48+6);

UTouch myTouch(5, 4, 7, 6, 16+6);

uint32_t cx, cy;
uint32_t rx[8], ry[8];
uint32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center;
uint32_t calx, caly, cals;
char buf[13];

void setupLCD()
{
	myGLCD.InitLCD(PORTRAIT);
	myGLCD.setFont(SmallFont);
	myGLCD.clrScr();

	myTouch.InitTouch(TOUCH_ORIENTATION);
	dispx=myGLCD.getDisplayXSize();
	dispy=myGLCD.getDisplayYSize();
	text_y_center=(dispy/2)-6;
}

void fail()
{
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, dispx-1, 13);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.drawLine(0, 14, dispx-1, 14);
  myGLCD.print("UTouch Calibration FAILED", CENTER, 1);
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.print("Unable to read the position", LEFT, 30);
  myGLCD.print("of the press. This is a", LEFT, 42);
  myGLCD.print("hardware issue and can", 88, 54);
  myGLCD.print("not be corrected in", LEFT, 66);
  myGLCD.print("software.", LEFT, 78);

  while(true) {};
}

void drawCrossHair(int x, int y)
{
  myGLCD.drawRect(x-10, y-10, x+10, y+10);
  myGLCD.drawLine(x-5, y, x+5, y);
  myGLCD.drawLine(x, y-5, x, y+5);
}

void readCoordinates()
{
  int iter = 5000;
  int failcount = 0;
  int cnt = 0;
  uint32_t tx=0;
  uint32_t ty=0;
  boolean OK = false;

  while (OK == false)
  {
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("*  PRESS  *", CENTER, text_y_center);
    while (myTouch.dataAvailable() == false) {}
    myGLCD.print("*  HOLD!  *", CENTER, text_y_center);
    while ((myTouch.dataAvailable() == true) && (cnt<iter) && (failcount<10000))
    {
      myTouch.calibrateRead();
      if (!((myTouch.TP_X==65535) || (myTouch.TP_Y==65535)))
      {
        tx += myTouch.TP_X;
        ty += myTouch.TP_Y;
        cnt++;
      }
      else
        failcount++;
    }
    if (cnt>=iter)
    {
      OK = true;
    }
    else
    {
      tx = 0;
      ty = 0;
      cnt = 0;
    }
    if (failcount>=10000)
      fail();
  }

  cx = tx / iter;
  cy = ty / iter;
}

void calibrate(int x, int y, int i)
{
  myGLCD.setColor(255, 255, 255);
  drawCrossHair(x,y);
  myGLCD.setBackColor(255, 0, 0);
  readCoordinates();
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("* RELEASE *", CENTER, text_y_center);
  myGLCD.setColor(80, 80, 80);
  drawCrossHair(x,y);
  rx[i]=cx;
  ry[i]=cy;
  while (myTouch.dataAvailable() == true) {}
}

void waitForTouch()
{
  while (myTouch.dataAvailable() == true) {}
  while (myTouch.dataAvailable() == false) {}
  while (myTouch.dataAvailable() == true) {}
}

void toHex(uint32_t num)
{
  buf[0] = '0';
  buf[1] = 'x';
  buf[10] = 'U';
  buf[11] = 'L';
  buf[12] = 0;
  for (int zz=9; zz>1; zz--)
  {
    if ((num & 0xF) > 9)
      buf[zz] = (num & 0xF) + 55;
    else
      buf[zz] = (num & 0xF) + 48;
    num=num>>4;
  }
}

void startup()
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, dispx-1, 13);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.drawLine(0, 14, dispx-1, 14);
  myGLCD.print("UTouch Calibration", CENTER, 1);
  myGLCD.setBackColor(0, 0, 0);

  if (dispx==220)
  {
    myGLCD.print("Use a stylus or something", LEFT, 30);
    myGLCD.print("similar to touch as close", LEFT, 42);
    myGLCD.print("to the center of the", LEFT, 54);
    myGLCD.print("highlighted crosshair as", LEFT, 66);
    myGLCD.print("possible. Keep as still as", LEFT, 78);
    myGLCD.print("possible and keep holding", LEFT, 90);
    myGLCD.print("until the highlight is", LEFT, 102);
    myGLCD.print("removed. Repeat for all", LEFT, 114);
    myGLCD.print("crosshairs in sequence.", LEFT, 126);
    myGLCD.print("Touch screen to continue", CENTER, 162);
  }
  else
  {
    myGLCD.print("INSTRUCTIONS", CENTER, 30);
    myGLCD.print("Use a stylus or something similar to", LEFT, 50);
    myGLCD.print("touch as close to the center of the", LEFT, 62);
    myGLCD.print("highlighted crosshair as possible. Keep", LEFT, 74);
    myGLCD.print("as still as possible and keep holding", LEFT, 86);
    myGLCD.print("until the highlight is removed. Repeat", LEFT, 98);
    myGLCD.print("for all crosshairs in sequence.", LEFT, 110);

    myGLCD.print("Further instructions will be displayed", LEFT, 134);
    myGLCD.print("when the calibration is complete.", LEFT, 146);

    myGLCD.print("Do NOT use your finger as a calibration", LEFT, 170);
    myGLCD.print("stylus or the result WILL BE imprecise.", LEFT, 182);

    myGLCD.print("Touch screen to continue", CENTER, 226);
  }

  waitForTouch();
  myGLCD.clrScr();
}

void done()
{
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, dispx-1, 13);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.drawLine(0, 14, dispx-1, 14);
  myGLCD.print("UTouch Calibration", CENTER, 1);
  myGLCD.setBackColor(0, 0, 0);

  if (dispx==220)
  {
    myGLCD.print("To use the new calibration", LEFT, 30);
    myGLCD.print("settings you must edit the", LEFT, 42);
    myGLCD.setColor(160, 160, 255);
    myGLCD.print("UTouchCD.h", LEFT, 54);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("file and change", 88, 54);
    myGLCD.print("the following values. The", LEFT, 66);
    myGLCD.print("values are located right", LEFT, 78);
    myGLCD.print("below the opening comment.", LEFT, 90);
    myGLCD.print("CAL_X", LEFT, 110);
    myGLCD.print("CAL_Y", LEFT, 122);
    myGLCD.print("CAL_S", LEFT, 134);
    toHex(calx);
    myGLCD.print(buf, 75, 110);
    toHex(caly);
    myGLCD.print(buf, 75, 122);
    toHex(cals);
    myGLCD.print(buf, 75, 134);
  }
  else
  {
    myGLCD.print("CALIBRATION COMPLETE", CENTER, 30);
    myGLCD.print("To use the new calibration", LEFT, 50);
    myGLCD.print("settings you must edit the", LEFT, 62);
    myGLCD.setColor(160, 160, 255);
    myGLCD.print("UTouchCD.h", LEFT, 74);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("file and change", 88, 74);
    myGLCD.print("the following values.", LEFT, 86);
    myGLCD.print("The values are located right", LEFT, 98);
    myGLCD.print("below the opening comment in", LEFT, 110);
    myGLCD.print("the file.", LEFT, 122);
    myGLCD.print("CAL_X", LEFT, 150);
    myGLCD.print("CAL_Y", LEFT, 162);
    myGLCD.print("CAL_S", LEFT, 174);

    toHex(calx);
    myGLCD.print(buf, 75, 150);
    toHex(caly);
    myGLCD.print(buf, 75, 162);
    toHex(cals);
    myGLCD.print(buf, 75, 174);
  }

}

void writeLCD(uint16 data, uint8 toRegister)
{
	gpio_write_bit(GPIOD, 14, data & 0x01);
	gpio_write_bit(GPIOD, 15, data>>1 & 0x01);
	gpio_write_bit(GPIOD, 0, data>>2 & 0x01);
	gpio_write_bit(GPIOD, 1, data>>3 & 0x01);
	gpio_write_bit(GPIOE, 7, data>>4 & 0x01);
	gpio_write_bit(GPIOE, 8, data>>5 & 0x01);
	gpio_write_bit(GPIOE, 9, data>>6 & 0x01);
	gpio_write_bit(GPIOE, 10, data>>7 & 0x01);

	gpio_write_bit(GPIOE, 11, data>>8 & 0x01);
	gpio_write_bit(GPIOE, 12, data>>9 & 0x01);
	gpio_write_bit(GPIOE, 13, data>>10 & 0x01);
	gpio_write_bit(GPIOE, 14, data>>11 & 0x01);
	gpio_write_bit(GPIOE, 15, data>>12 & 0x01);
	gpio_write_bit(GPIOD, 8, data>>13 & 0x01);
	gpio_write_bit(GPIOD, 9, data>>14 & 0x01);
	gpio_write_bit(GPIOD, 10, data>>15 & 0x01);

	gpio_write_bit(GPIOD, 7, 0);
	gpio_write_bit(GPIOD, 11, !toRegister);
	gpio_write_bit(GPIOD, 5, 0);
	delay_us(10);
	gpio_write_bit(GPIOD, 7, 1);
	gpio_write_bit(GPIOD, 11, 1);
	gpio_write_bit(GPIOD, 5, 1);
}

uint16 readLCD()
{
	uint16 data;
	gpio_set_mode(GPIOD, 14, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOD, 15, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOD, 0, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOD, 1, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 7, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 8, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 9, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 10, GPIO_INPUT_FLOATING);

	gpio_set_mode(GPIOE, 11, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 12, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 13, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 14, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOE, 15, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOD, 8, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOD, 9, GPIO_INPUT_FLOATING);
	gpio_set_mode(GPIOD, 10, GPIO_INPUT_FLOATING);

	data=0;
	gpio_write_bit(GPIOD, 7, 0);
	gpio_write_bit(GPIOD, 4, 0);
	delay_us(10);

	data=data | (gpio_read_bit(GPIOD, 14)>>14);
	data=data | (gpio_read_bit(GPIOD, 15)>>15)<<1;
	data=data | (gpio_read_bit(GPIOD, 0))<<2;
	data=data | (gpio_read_bit(GPIOD, 1)>>1)<<3;
	data=data | (gpio_read_bit(GPIOE, 7)>>7)<<4;
	data=data | (gpio_read_bit(GPIOE, 8)>>8)<<5;
	data=data | (gpio_read_bit(GPIOE, 9)>>9)<<6;
	data=data | (gpio_read_bit(GPIOE, 10)>>10)<<7;

	data=data | (gpio_read_bit(GPIOE, 11)>>11)<<8;
	data=data | (gpio_read_bit(GPIOE, 12)>>12)<<9;
	data=data | (gpio_read_bit(GPIOE, 13)>>13)<<10;
	data=data | (gpio_read_bit(GPIOE, 14)>>14)<<11;
	data=data | (gpio_read_bit(GPIOE, 15)>>15)<<12;
	data=data | (gpio_read_bit(GPIOD, 8)>>8)<<13;
	data=data | (gpio_read_bit(GPIOD, 9)>>9)<<14;
	data=data | (gpio_read_bit(GPIOD, 10)>>10)<<15;

	delay_us(10);
	gpio_write_bit(GPIOD, 7, 1);
	gpio_write_bit(GPIOD, 4, 1);
	gpio_set_mode(GPIOD, 14, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOD, 15, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOD, 0, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOD, 1, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 7, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 8, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 9, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 10, GPIO_OUTPUT_PP);

	gpio_set_mode(GPIOE, 11, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 12, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 13, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 14, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOE, 15, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOD, 8, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOD, 9, GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOD, 10, GPIO_OUTPUT_PP);

	return data;
}

void runLCD()
{
	//	  startup();
	//
	//	  myGLCD.setColor(80, 80, 80);
	//	  drawCrossHair(dispx-11, 10);
	//	  drawCrossHair(dispx/2, 10);
	//	  drawCrossHair(10, 10);
	//	  drawCrossHair(dispx-11, dispy/2);
	//	  drawCrossHair(10, dispy/2);
	//	  drawCrossHair(dispx-11, dispy-11);
	//	  drawCrossHair(dispx/2, dispy-11);
	//	  drawCrossHair(10, dispy-11);
	//	  myGLCD.setColor(255, 255, 255);
	//	  myGLCD.setBackColor(255, 0, 0);
	//	  myGLCD.print("***********", CENTER, text_y_center-12);
	//	  myGLCD.print("***********", CENTER, text_y_center+12);
	//
	//	  calibrate(10, 10, 0);
	//	  calibrate(10, dispy/2, 1);
	//	  calibrate(10, dispy-11, 2);
	//	  calibrate(dispx/2, 10, 3);
	//	  calibrate(dispx/2, dispy-11, 4);
	//	  calibrate(dispx-11, 10, 5);
	//	  calibrate(dispx-11, dispy/2, 6);
	//	  calibrate(dispx-11, dispy-11, 7);
	//
	//	  if (TOUCH_ORIENTATION == LANDSCAPE)
	//	    cals=(long(dispx-1)<<12)+(dispy-1);
	//	  else
	//	    cals=(long(dispy-1)<<12)+(dispx-1);
	//
	//	  if (TOUCH_ORIENTATION == PORTRAIT)
	//	    px = abs(((float(rx[2]+rx[4]+rx[7])/3)-(float(rx[0]+rx[3]+rx[5])/3))/(dispy-20));  // PORTRAIT
	//	  else
	//	    px = abs(((float(rx[5]+rx[6]+rx[7])/3)-(float(rx[0]+rx[1]+rx[2])/3))/(dispy-20));  // LANDSCAPE
	//
	//	  if (TOUCH_ORIENTATION == PORTRAIT)
	//	  {
	//	    clx = (((rx[0]+rx[3]+rx[5])/3));  // PORTRAIT
	//	    crx = (((rx[2]+rx[4]+rx[7])/3));  // PORTRAIT
	//	  }
	//	  else
	//	  {
	//	    clx = (((rx[0]+rx[1]+rx[2])/3));  // LANDSCAPE
	//	    crx = (((rx[5]+rx[6]+rx[7])/3));  // LANDSCAPE
	//	  }
	//	  if (clx<crx)
	//	  {
	//	    clx = clx - (px*10);
	//	    crx = crx + (px*10);
	//	  }
	//	  else
	//	  {
	//	    clx = clx + (px*10);
	//	    crx = crx - (px*10);
	//	  }
	//
	//	  if (TOUCH_ORIENTATION == PORTRAIT)
	//	    py = abs(((float(ry[5]+ry[6]+ry[7])/3)-(float(ry[0]+ry[1]+ry[2])/3))/(dispx-20));  // PORTRAIT
	//	  else
	//	    py = abs(((float(ry[0]+ry[3]+ry[5])/3)-(float(ry[2]+ry[4]+ry[7])/3))/(dispx-20));  // LANDSCAPE
	//
	//	  if (TOUCH_ORIENTATION == PORTRAIT)
	//	  {
	//	    cty = (((ry[5]+ry[6]+ry[7])/3));  // PORTRAIT
	//	    cby = (((ry[0]+ry[1]+ry[2])/3));  // PORTRAIT
	//	  }
	//	  else
	//	  {
	//	    cty = (((ry[0]+ry[3]+ry[5])/3));  // LANDSCAPE
	//	    cby = (((ry[2]+ry[4]+ry[7])/3));  // LANDSCAPE
	//	  }
	//	  if (cty<cby)
	//	  {
	//	    cty = cty - (py*10);
	//	    cby = cby + (py*10);
	//	  }
	//	  else
	//	  {
	//	    cty = cty + (py*10);
	//	    cby = cby - (py*10);
	//	  }
	//
	//	  calx = (long(clx)<<14) + long(crx);
	//	  caly = (long(cty)<<14) + long(cby);
	//	  if (TOUCH_ORIENTATION == LANDSCAPE)
	//	    cals = cals + (1L<<31);
	//
	//	  done();
	//
	//	  delay(120000);

		  myGLCD.clrScr();
		  myTouch.setPrecision(PREC_EXTREME);
		  long x, y;

		  while(1)
		  {
			  while (myTouch.dataAvailable() == true)
			  {
				myTouch.read();
				x = myTouch.getX();
				y = myTouch.getY();
				if ((x!=-1) and (y!=-1))
				{
				  myGLCD.drawPixel (x, y);
				}
			  }
		  }

	//	int buf[318];
	//	int x, x2;
	//	int y, y2;
	//	int r;
	//	uint16 devCode;
	//
	////	GPIOB->regs->BSRR=0x0003;
	//	GPIOB->regs->ODR=GPIOB->regs->ODR | 0x0003; //0b0000 0000 0000 0011
	//	delay(1000);
	////	GPIOB->regs->BSRR=0x0003;
	//	GPIOB->regs->ODR=GPIOB->regs->ODR ^ 0x0003;
	//	delay(100);
	//
	//	Serial1.println("test1");
	//
	////	writeLCD(0, 1);
	////	devCode=readLCD();
	//
	////	Serial1.println(devCode, HEX);
	//
	////	writeLCD(0x00, 1);
	////	writeLCD(0x0001, 0);
	////
	////	writeLCD(0x03, 1);
	////	writeLCD(0xA8A4, 0);
	//
	//
	//
	//
	//	// Clear the screen and draw the frame
	//	myGLCD.clrScr();
	//
	//	myGLCD.setColor(255, 0, 0);
	//	myGLCD.fillRect(0, 0, 319, 13);
	//	myGLCD.setColor(64, 64, 64);
	//	myGLCD.fillRect(0, 226, 319, 239);
	//	myGLCD.setColor(255, 255, 255);
	//	myGLCD.setBackColor(255, 0, 0);
	//	myGLCD.print("* Universal Color TFT Display Library *", CENTER, 1);
	//	myGLCD.setBackColor(64, 64, 64);
	//	myGLCD.setColor(255,255,0);
	//	myGLCD.print("<http://electronics.henningkarlsen.com>", CENTER, 227);
	//
	//	myGLCD.setColor(0, 0, 255);
	//	myGLCD.drawRect(0, 14, 319, 225);
	//
	//	// Draw crosshairs
	//	myGLCD.setColor(0, 0, 255);
	//	myGLCD.setBackColor(0, 0, 0);
	//	myGLCD.drawLine(159, 15, 159, 224);
	//	myGLCD.drawLine(1, 119, 318, 119);
	//	for (int i=9; i<310; i+=10)
	//		myGLCD.drawLine(i, 117, i, 121);
	//	for (int i=19; i<220; i+=10)
	//		myGLCD.drawLine(157, i, 161, i);
	//
	//	// Draw sin-, cos- and tan-lines
	//	myGLCD.setColor(0,255,255);
	//	myGLCD.print("Sin", 5, 15);
	//	for (int i=1; i<318; i++)
	//	{
	//		myGLCD.drawPixel(i,119+(sin(((i*1.13)*3.14)/180)*95));
	//	}
	//
	//	myGLCD.setColor(255,0,0);
	//	myGLCD.print("Cos", 5, 27);
	//	for (int i=1; i<318; i++)
	//	{
	//		myGLCD.drawPixel(i,119+(cos(((i*1.13)*3.14)/180)*95));
	//	}
	//
	//	myGLCD.setColor(255,255,0);
	//	myGLCD.print("Tan", 5, 39);
	//	for (int i=1; i<318; i++)
	//	{
	//		myGLCD.drawPixel(i,119+(tan(((i*1.13)*3.14)/180)));
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//	myGLCD.setColor(0, 0, 255);
	//	myGLCD.setBackColor(0, 0, 0);
	//	myGLCD.drawLine(159, 15, 159, 224);
	//	myGLCD.drawLine(1, 119, 318, 119);
	//
	//	// Draw a moving sinewave
	//	x=1;
	//	for (int i=1; i<(318*20); i++)
	//	{
	//		x++;
	//		if (x==319)
	//			x=1;
	//		if (i>319)
	//		{
	//			if ((x==159)||(buf[x-1]==119))
	//				myGLCD.setColor(0,0,255);
	//			else
	//				myGLCD.setColor(0,0,0);
	//			myGLCD.drawPixel(x,buf[x-1]);
	//		}
	//		myGLCD.setColor(0,255,255);
	//		y=119+(sin(((i*1.1)*3.14)/180)*(90-(i / 100)));
	//		myGLCD.drawPixel(x,y);
	//		buf[x-1]=y;
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some filled rectangles
	//	for (int i=1; i<6; i++)
	//	{
	//		switch (i)
	//		{
	//		case 1:
	//			myGLCD.setColor(255,0,255);
	//			break;
	//		case 2:
	//			myGLCD.setColor(255,0,0);
	//			break;
	//		case 3:
	//			myGLCD.setColor(0,255,0);
	//			break;
	//		case 4:
	//			myGLCD.setColor(0,0,255);
	//			break;
	//		case 5:
	//			myGLCD.setColor(255,255,0);
	//			break;
	//		}
	//		myGLCD.fillRect(70+(i*20), 30+(i*20), 130+(i*20), 90+(i*20));
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some filled, rounded rectangles
	//	for (int i=1; i<6; i++)
	//	{
	//		switch (i)
	//		{
	//		case 1:
	//			myGLCD.setColor(255,0,255);
	//			break;
	//		case 2:
	//			myGLCD.setColor(255,0,0);
	//			break;
	//		case 3:
	//			myGLCD.setColor(0,255,0);
	//			break;
	//		case 4:
	//			myGLCD.setColor(0,0,255);
	//			break;
	//		case 5:
	//			myGLCD.setColor(255,255,0);
	//			break;
	//		}
	//		myGLCD.fillRoundRect(190-(i*20), 30+(i*20), 250-(i*20), 90+(i*20));
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some filled circles
	//	for (int i=1; i<6; i++)
	//	{
	//		switch (i)
	//		{
	//		case 1:
	//			myGLCD.setColor(255,0,255);
	//			break;
	//		case 2:
	//			myGLCD.setColor(255,0,0);
	//			break;
	//		case 3:
	//			myGLCD.setColor(0,255,0);
	//			break;
	//		case 4:
	//			myGLCD.setColor(0,0,255);
	//			break;
	//		case 5:
	//			myGLCD.setColor(255,255,0);
	//			break;
	//		}
	//		myGLCD.fillCircle(100+(i*20),60+(i*20), 30);
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some lines in a pattern
	//	myGLCD.setColor (255,0,0);
	//	for (int i=15; i<224; i+=5)
	//	{
	//		myGLCD.drawLine(1, i, (i*1.44)-10, 224);
	//	}
	//	myGLCD.setColor (255,0,0);
	//	for (int i=224; i>15; i-=5)
	//	{
	//		myGLCD.drawLine(318, i, (i*1.44)-11, 15);
	//	}
	//	myGLCD.setColor (0,255,255);
	//	for (int i=224; i>15; i-=5)
	//	{
	//		myGLCD.drawLine(1, i, 331-(i*1.44), 15);
	//	}
	//	myGLCD.setColor (0,255,255);
	//	for (int i=15; i<224; i+=5)
	//	{
	//		myGLCD.drawLine(318, i, 330-(i*1.44), 224);
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some random circles
	//	for (int i=0; i<100; i++)
	//	{
	//		myGLCD.setColor(random(255), random(255), random(255));
	//		x=32+random(256);
	//		y=45+random(146);
	//		r=random(30);
	//		myGLCD.drawCircle(x, y, r);
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some random rectangles
	//	for (int i=0; i<100; i++)
	//	{
	//		myGLCD.setColor(random(255), random(255), random(255));
	//		x=2+random(316);
	//		y=16+random(207);
	//		x2=2+random(316);
	//		y2=16+random(207);
	//		myGLCD.drawRect(x, y, x2, y2);
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	// Draw some random rounded rectangles
	//	for (int i=0; i<100; i++)
	//	{
	//		myGLCD.setColor(random(255), random(255), random(255));
	//		x=2+random(316);
	//		y=16+random(207);
	//		x2=2+random(316);
	//		y2=16+random(207);
	//		myGLCD.drawRoundRect(x, y, x2, y2);
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	for (int i=0; i<100; i++)
	//	{
	//		myGLCD.setColor(random(255), random(255), random(255));
	//		x=2+random(316);
	//		y=16+random(209);
	//		x2=2+random(316);
	//		y2=16+random(209);
	//		myGLCD.drawLine(x, y, x2, y2);
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.setColor(0,0,0);
	//	myGLCD.fillRect(1,15,318,224);
	//
	//	for (int i=0; i<10000; i++)
	//	{
	//		myGLCD.setColor(random(255), random(255), random(255));
	//		myGLCD.drawPixel(2+random(316), 16+random(209));
	//	}
	//
	//	delay(2000);
	//
	//	myGLCD.fillScr(0, 0, 255);
	//	myGLCD.setColor(255, 0, 0);
	//	myGLCD.fillRoundRect(80, 70, 239, 169);
	//
	//	myGLCD.setColor(255, 255, 255);
	//	myGLCD.setBackColor(255, 0, 0);
	//	myGLCD.print("That's it!", CENTER, 93);
	//	myGLCD.print("Restarting in a", CENTER, 119);
	//	myGLCD.print("few seconds...", CENTER, 132);
	//
	//	myGLCD.setColor(0, 255, 0);
	//	myGLCD.setBackColor(0, 0, 255);
	//	myGLCD.print("Runtime: (msecs)", CENTER, 210);
	//	myGLCD.printNumI(millis(), CENTER, 225);
	//
	//	delay (10000);
}


//	int fontX;
//	int fontY;
//	int xPoint;

//	fontX=display->getScreen()->getFontXsize();
//	fontY=display->getScreen()->getFontYsize();
//	for(int i=0; i<2; i++)
//	{
//		xPoint=fontX*15*i;
//		for(int j=0; j<4; j++)
//		{
//			display->print("tetrode", xPoint, j*5*fontY);
//			display->printNumI(i*4+j+1, xPoint+fontX*7, j*5*fontY, 1);
//			Serial1.print("tetrode");
//			Serial1.println(i*4+j+1);
//			for(int k=0; k<4; k++)
//			{
//				display->print("ch", xPoint, (j*5+k+1)*fontY);
//				display->printNumI(k+1, xPoint+fontX*2, (j*5+k+1)*fontY, 1);
//				tetrodes[i*4+j].channels[k]->activateChannel();
//				tetrodes[i*4+j].channels[k]->impedance=impedance.measureImpedance();
//				Serial1.println(tetrodes[i*4+j].channels[k]->impedance);
//
//				display->printNumI(tetrodes[i*4+j].channels[k]->impedance,
//						xPoint+fontX*4, (j*5+k+1)*fontY, 8);
//			}
//		}
//	}
