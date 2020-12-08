/*
 * LCD.c
 *
 * Created: 11/7/2020 10:42:34 AM
 *  Author: ENG Mostafa
 */ 
#include "LCD.h"

static void SendFallingEdge(void)
{
	SET_BIT(PORTC,EN) ;
	_delay_ms(5) ;
	CLR_BIT(PORTC,EN) ;
	_delay_ms(5) ;
}
void LCD_vPrintData(uint8 *str)
{
   while (*str)
   {
	   LCD_vSendData(*str++) ;
   }
}
void LCD_vCleanScreen(void)
{
	LCD_vSendCmd(CLEAR_LCD) ;
}
void LCD_vMoveCursor(uint8 row, uint8 col)
{
	uint8 temp ;
	if(row == 0)  /* ox80 - 0x8f */
	{
		temp = FIRST_ROW + col ;
	}
	else
	{
		temp = SECOND_ROW + col ;
	}
	LCD_vSendCmd(temp) ;
}
#ifdef LED_8_BIT
void LCD_vInit(void)
{
	// SET RS,RW,EN '1'
	SET_BIT(DDRC,RS);
	SET_BIT(DDRC,RW);
	SET_BIT(DDRC,EN);
	//PORTA OUTPUT
	SET_REG(DDRA);
	// RW clear to be write
	CLR_BIT(PORTC,RW) ;
	//Commands
	// Initialization
	LCD_vSendCmd(INITIALIZATION_8) ;
	// Clear screen
	LCD_vSendCmd(CLEAR_LCD) ;
	// Blink Cursor
	LCD_vSendCmd(BLINK_CURSOR) ;
	_delay_ms(20) ;
}
void LCD_vSendCmd(uint8 cmd)
{
	// put Data on data lines
	PORTA = cmd ;
	// Choose Rs=0
	CLR_BIT(PORTC,RS) ;
	//send falling edge
	SendFallingEdge();
}
void LCD_vSendData(uint8 data)
{
	// put Data on data lines
	PORTA = data ;
	// Choose Rs=1
	SET_BIT(PORTC,RS) ;
	//send falling edge
	SendFallingEdge();
}

#else /* #define LCD_4_BIT  */

void LCD_vInit(void)
{
	// SET RS,RW,EN '1'
	SET_BIT(DDRC,RS);
	SET_BIT(DDRC,RW);
	SET_BIT(DDRC,EN);
	//4-MSBBins_PORTA OUTPUT
	SET_BIT(DDRA,4);
	SET_BIT(DDRA,5);
	SET_BIT(DDRA,6);
	SET_BIT(DDRA,7);
	// RW clear to be write
	CLR_BIT(PORTC,RW) ;
	//Commands
	// Initialization
	LCD_vSendCmd(INITIALIZATION_4_1) ;
	_delay_ms(1);
	LCD_vSendCmd(INITIALIZATION_4_2) ;
	_delay_ms(1);
	LCD_vSendCmd(INITIALIZATION_4_3) ;
	_delay_ms(1);
	// Clear screen
	LCD_vSendCmd(CLEAR_LCD) ;
	// Blink Cursor
	LCD_vSendCmd(BLINK_CURSOR) ;
	_delay_ms(20) ;
}
void LCD_vSendCmd(uint8 cmd)
{
	// put 4MSB_Data on data lines
	PORTA &=LSB ;
	PORTA |=(cmd&MSB);
	// Choose Rs=0
	CLR_BIT(PORTC,RS) ;
	//send falling edge
	SendFallingEdge();
	// put 4LSB_Data on data lines
	PORTA &=LSB;
	PORTA |= (cmd<<4) ;
	CLR_BIT(PORTC,RS);
	SendFallingEdge();
}
void LCD_vSendData(uint8 data)
{
	// put 4MSB_Data on data lines
	PORTA &=LSB ;
	PORTA |=(data&MSB);
	// Choose Rs=0
	SET_BIT(PORTC,RS) ;
	//send falling edge
	SendFallingEdge();
	// put 4LSB_Data on data lines
	PORTA &=LSB;
	PORTA |= (data<<4) ;
	SET_BIT(PORTC,RS);
	SendFallingEdge();
}
#endif