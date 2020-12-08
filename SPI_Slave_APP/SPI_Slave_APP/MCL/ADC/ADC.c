/*
 * ADC.c
 *
 * Created: 11/14/2020 12:03:24 PM
 *  Author: ENG Mostafa
 */ 
#include "ADC.h"

void ADC_vInit()
{
	// ENABLE ADC
	   SET_BIT(ADCSRA,ADEN);
	// Adjust VREF ----> AVcc
	SET_BIT(ADMUX,REFS0) ;
	CLR_BIT(ADMUX,REFS1) ;
	// Adjust prescaler --> 128
	SET_BIT(ADCSRA,ADPS0) ;
	SET_BIT(ADCSRA,ADPS1) ; 
	SET_BIT(ADCSRA,ADPS2) ;
	// INTERRUPTS ON 
	SET_BIT(ADCSRA,ADIE) ;
}
// IF INTERRUPTS OFF
uint16 ADC_u16Read(uint8 channel)   // CH0 --- CH7
{
	uint16 temp ;
	// CHOOCE CHANNEL 
	ADMUX |= channel ;
	// START CONVERSATION
	SET_BIT(ADCSRA,ADSC) ; 
	// CHECH IF CONVERSION FINISHED
    while ( READ_BIT(ADCSRA,ADIF) == 0 )  // ADID=1 if it ready
    	 { /*wait */ }
	// RETURN CONVERSION VALUE   // Note should read ADCL THEN ADCH
	temp = (uint16)ADCL ; 
	temp |= (uint16) (ADCH<<8);
	return temp; 
} 
// IF INTERRUPTS ON
void ADC_vStartConversion()
{
	// CHOOCE CHANNEL 
	ADMUX |= 1 ;
	// START CONVERSATION
	SET_BIT(ADCSRA,ADSC) ;
}