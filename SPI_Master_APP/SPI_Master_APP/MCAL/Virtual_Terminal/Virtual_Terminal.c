/*
 * Virtual_Terminal.c
 *
 * Created: 12/5/2020 9:00:06 PM
 *  Author: ENG Mostafa
 */ 
#include "Virtual_Terminal.h"

void VirtTerm_vInit()
{
	UART_vInit(BAUD_RATE) ;
}
void VirtTerm_vSend(uint8 data)
{
	UART_vSend(data) ;
}
void VirtTerm_vPrint(uint8* str)
{
	uint8* ptr = str;
	while(*ptr)
	{
		VirtTerm_vSend(*ptr++) ;
	}
}
