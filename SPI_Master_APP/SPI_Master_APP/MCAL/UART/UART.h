/*
 * UART.h
 *
 * Created: 11/21/2020 10:46:53 AM
 *  Author: ENG Mostafa
 */ 

/*
#ifndef UART_H_
#define UART_H_
#include "Std_macros.h"
#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h> 
#define F_CPU 16000000UL
void UART_vTnit(uint32 baud_rate);
void UART_vSend( uint8 data);
*/

#ifndef UART_H_
#define UART_H_
#include "Std_macros.h"
#include "std_types.h"
void UART_vInit(uint32 baud);
void UART_vSend(uint8 val);


#endif

