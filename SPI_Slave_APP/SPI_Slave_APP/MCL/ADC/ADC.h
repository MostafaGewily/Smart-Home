/*
 * ADC.h
 *
 * Created: 11/14/2020 12:03:35 PM
 *  Author: ENG Mostafa
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Std_macros.h"
#include "std_types.h"
#include <avr/io.h>

void ADC_vInit();
uint16 ADC_u16Read(uint8 channel);
void ADC_vStartConversion();


#endif /* ADC_H_ */