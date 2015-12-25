/*
 *  HW_STM32F1.h
 *  
 *
 *  Created by consciousness on 5/22/14.
 *  Copyright 2014 UT Austin. All rights reserved.
 *
 */

#include <libmaple/gpio.h>

// *** Hardwarespecific functions ***

static const uint16 gpioDMask=~0xC703;
static const uint16 gpioEMask=~0xFF80;

regtype *portOutputRegister(const gpio_dev *port)
{
	return &(port->regs->ODR);
}

const gpio_dev *digitalPinToPort(int pin)
{
	const gpio_dev *temp[]={GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};

	return temp[pin/16];
}

regsize digitalPinToBitMask(int pin)
{
	return (0x01<<(pin%16));
}


void UTFT::_hw_special_init()
{
}

void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)
{   
	switch (mode)
	{
		case 1:
			if (display_serial_mode==SERIAL_4PIN)
			{
				if (VH==1)
					sbi(P_SDA, B_SDA);
				else
					cbi(P_SDA, B_SDA);
				pulse_low(P_SCL, B_SCL);
			}
			else
			{
				if (VH==1)
					sbi(P_RS, B_RS);
				else
					cbi(P_RS, B_RS);
			}
			
			if (VL & 0x80)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x40)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x20)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x10)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x08)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x04)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x02)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			if (VL & 0x01)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
			break;
		case 8:
//			GPIOD->regs->BSRR=0xC003C003;
//			GPIOE->regs->BSRR=0x07800780;

//			REG_PIOA_CODR=0x0000C000;
//			REG_PIOD_CODR=0x0000064F;

//			GPIOD->regs->ODR |= (VH & 0x03 << 14) | (VH & 0x0C >> 2);
//			GPIOE->regs->ODR |= (VH & 0xF0 << 3);

			pulse_low(P_WR, B_WR);
			
//			GPIOD->regs->BSRR=0x0000C003;
//			GPIOE->regs->BSRR=0x00000780;
//
//			GPIOD->regs->ODR |= (VL & 0x03 << 14) | (VL & 0x0C >> 2);
//			GPIOE->regs->ODR |= (VL & 0xF0 << 3);

			pulse_low(P_WR, B_WR);
			break;
		case 16:
			GPIOD->regs->ODR=(GPIOD->regs->ODR & gpioDMask)
					| ((VL & 0x0003)<<14)
					| ((VL & 0x000C)>>2)
					| ((VH & 0x00E0)<<3);

			GPIOE->regs->ODR=(GPIOE->regs->ODR & gpioEMask)
					| ((VL & 0x00F0)<<3)
					| ((VH & 0x001F)<<11);

//			gpio_write_bit(GPIOD, 14, VL & 0x01);
//			gpio_write_bit(GPIOD, 15, VL>>1 & 0x01);
//			gpio_write_bit(GPIOD, 0, VL>>2 & 0x01);
//			gpio_write_bit(GPIOD, 1, VL>>3 & 0x01);
//			gpio_write_bit(GPIOE, 7, VL>>4 & 0x01);
//			gpio_write_bit(GPIOE, 8, VL>>5 & 0x01);
//			gpio_write_bit(GPIOE, 9, VL>>6 & 0x01);
//			gpio_write_bit(GPIOE, 10, VL>>7 & 0x01);
//
//			gpio_write_bit(GPIOE, 11, VH & 0x01);
//			gpio_write_bit(GPIOE, 12, VH>>1 & 0x01);
//			gpio_write_bit(GPIOE, 13, VH>>2 & 0x01);
//			gpio_write_bit(GPIOE, 14, VH>>3 & 0x01);
//			gpio_write_bit(GPIOE, 15, VH>>4 & 0x01);
//			gpio_write_bit(GPIOD, 8, VH>>5 & 0x01);
//			gpio_write_bit(GPIOD, 9, VH>>6 & 0x01);
//			gpio_write_bit(GPIOD, 10, VH>>7 & 0x01);

			pulse_low(P_WR, B_WR);
			break;
		case LATCHED_16:
			asm("nop");		// Mode is unsupported
			break;
	}
}

void UTFT::_set_direction_registers(byte mode)
{
	if (mode!=LATCHED_16)
	{
		gpio_set_mode(GPIOD, 14, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOD, 15, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOD, 0, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOD, 1, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOE, 7, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOE, 8, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOE, 9, GPIO_OUTPUT_PP);
		gpio_set_mode(GPIOE, 10, GPIO_OUTPUT_PP);
		if (mode==16)
		{
			gpio_set_mode(GPIOE, 11, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOE, 12, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOE, 13, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOE, 14, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOE, 15, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOD, 8, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOD, 9, GPIO_OUTPUT_PP);
			gpio_set_mode(GPIOD, 10, GPIO_OUTPUT_PP);
		}
	}
	else
	{
		asm("nop");		// Mode is unsupported
	}
}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

	GPIOD->regs->ODR=(GPIOD->regs->ODR & gpioDMask)
			| ((cl & 0x0003)<<14)
			| ((cl & 0x000C)>>2)
			| ((ch & 0x00E0)<<3);

	GPIOE->regs->ODR=(GPIOE->regs->ODR & gpioEMask)
			| ((cl & 0x00F0)<<3)
			| ((ch & 0x001F)<<11);

//	gpio_write_bit(GPIOD, 14, cl & 0x01);
//	gpio_write_bit(GPIOD, 15, cl>>1 & 0x01);
//	gpio_write_bit(GPIOD, 0, cl>>2 & 0x01);
//	gpio_write_bit(GPIOD, 1, cl>>3 & 0x01);
//	gpio_write_bit(GPIOE, 7, cl>>4 & 0x01);
//	gpio_write_bit(GPIOE, 8, cl>>5 & 0x01);
//	gpio_write_bit(GPIOE, 9, cl>>6 & 0x01);
//	gpio_write_bit(GPIOE, 10, cl>>7 & 0x01);
//
//	gpio_write_bit(GPIOE, 11, ch & 0x01);
//	gpio_write_bit(GPIOE, 12, ch>>1 & 0x01);
//	gpio_write_bit(GPIOE, 13, ch>>2 & 0x01);
//	gpio_write_bit(GPIOE, 14, ch>>3 & 0x01);
//	gpio_write_bit(GPIOE, 15, ch>>4 & 0x01);
//	gpio_write_bit(GPIOD, 8, ch>>5 & 0x01);
//	gpio_write_bit(GPIOD, 9, ch>>6 & 0x01);
//	gpio_write_bit(GPIOD, 10, ch>>7 & 0x01);
	
	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(P_WR, B_WR);
		}
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	long blocks;
	
//	GPIOD->regs->BSRR=0x0000C003;
//	GPIOE->regs->BSRR=0x00000780;
//
//	GPIOD->regs->ODR |= (ch & 0x03 << 14) | (ch & 0x0C >> 2);
//	GPIOE->regs->ODR |= (ch & 0xF0 << 3);
//	REG_PIOA_CODR=0x0000C000;
//	REG_PIOD_CODR=0x0000064F;
//	REG_PIOA_SODR=(ch & 0x06)<<13;
//	(ch & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;
//	REG_PIOD_SODR=((ch & 0x78)>>3) | ((ch & 0x80)>>1);

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		}
}
