/*
 * hardware.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: consciousness
 */

#include "../include/hardware.h"

CurrentSrc curSrc;
ImpedanceMeasure impedance(&resistorMap, &x8Map);
UTFT screen(SSD1289, 48+11, 48+5, 48+7, 48+6);
UTouch tPanel(5, 4, 7, 6, 16+6);

void initHardware()
{
	gpio_init_all();

	//initialize I2C
	i2c_init(I2C2);
	i2c_disable(I2C2);
	//clock setup must be done before enabling device
	//minimum of 2 MHz
	i2c_set_input_clk(I2C2, 2);
	//number of cycles for half period of SCL
	//set up for 10KHz
	//so far the clock seems to be stuck in 100KHz
	I2C2->regs->CCR=0x03E8;
	//i2c_set_clk_control(I2C2, 0x000003E8);
	//in standard mode, number of cycles per us+1
	i2c_set_trise(I2C2, 0x0003);
	i2c_master_enable(I2C2, 0);
	//end I2C initialization

	initChannels();

	screen.InitLCD(LANDSCAPE);

	tPanel.InitTouch(PORTRAIT);
	tPanel.setPrecision(PREC_EXTREME);


	impedance.init();
}
