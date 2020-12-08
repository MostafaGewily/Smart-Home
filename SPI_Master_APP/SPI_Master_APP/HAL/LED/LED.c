/*
 * LED.c
 *
 * Created: 11/20/2020 9:23:10 AM
 *  Author: ENG Mostafa
 */ 

#include "LED.h"

void LED_vInit()
{
	// Init LED0
	SET_BIT(DDRC,0);
	// Init LED1
	SET_BIT(DDRC,7);
	// Init LED2
	SET_BIT(DDRD,3) ;
}