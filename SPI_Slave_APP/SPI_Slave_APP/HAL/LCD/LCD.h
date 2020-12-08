/*
 * LCD.h
 *
 * Created: 11/7/2020 10:42:50 AM
 *  Author: ENG Mostafa
 */ 

#ifndef LCD_H_
#define LCD_H_

#define EN 3
#define RW 2
#define RS 1

#include <avr/io.h>
#include "std_types.h"
#include "Std_macros.h"
#include "LCD_cfg.h"
#define F_CPU 16000000UL
#include <util/delay.h>
void LCD_vSendCmd(uint8 cmd);
void LCD_vInit(void);
void LCD_vSendData(uint8 data);
void LCD_vPrintData(uint8 *str); 
void LCD_vCleanScreen(void);
void LCD_vMoveCursor(uint8 row, uint8 col) ;
#endif /* LCD_H_ */