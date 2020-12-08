/*
 * LED.c
 *
 * Created: 11/20/2020 9:23:10 AM
 *  Author: ENG Mostafa
 */ 

#include "LED.h"

void LED_vInit()
{
	// Init Room0
	SET_BIT(DDRD,0);
	// Init Room1
	SET_BIT(DDRD,1);
	// Init Air Conditioner
	SET_BIT(DDRD,2) ;
}