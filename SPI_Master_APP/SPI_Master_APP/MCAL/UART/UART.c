/*
 * UART.c
 *
 * Created: 11/21/2020 10:46:41 AM
 *  Author: ENG Mostafa
 */ 

#include "UART.h"
#include <avr/io.h>
#define F_CPU 16000000UL

void UART_vInit(uint32 baud)
{
	unsigned short ubrr;
		
	/*1 - Choose baud rate that will be used by sender and receiver by writing to UBRRL/UBRRH*/
	ubrr =  ( (F_CPU/ (16*baud)) - 1);
		
	UBRRL = (char) ubrr;
	UBRRH = (char) (ubrr >> 8);
	
	/*3 - Choose number of data bits to be sent from UCSRC We will work with 8 bits.*/
	UCSRC = (1<<URSEL)|(1<<UCSZ0) | (1<<UCSZ1);

	UCSRB |= (1<<RXCIE);
	
	/*2 - Enable UART Sender & Receiver*/
	UCSRB |= (1<<TXEN) | (1<<RXEN);
}

void UART_vSend(uint8 val)
{
	/*Wait for Transmit buffer to be empty*/
	while( (UCSRA & (1<<UDRE)) == 0 )
	{
	}
	/*Put data to transmit buffer*/
	UDR = val;
}

