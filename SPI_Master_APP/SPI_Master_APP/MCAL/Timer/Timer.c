/*
 * Timer.c
 *
 * Created: 11/20/2020 8:59:04 AM
 *  Author: ENG Mostafa
 */ 
#include "Timer.h"
#include <avr/interrupt.h>

void Timer0_vInit()
{
	// choose CTC Mode
	SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);
	// Select OCR0
	OCR0 = 152;
	// Enable Global I_bit
	sei() ;
	// Enable OCIE0 for TIMASK Register
	SET_BIT(TIMSK,OCIE0);
	// choose prescalar 1024
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	
}