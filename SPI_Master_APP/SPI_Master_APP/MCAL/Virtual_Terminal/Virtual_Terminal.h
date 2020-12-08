/*
 * Virtual_Terminal.h
 *
 * Created: 12/5/2020 8:59:54 PM
 *  Author: ENG Mostafa
 */ 


#ifndef VIRTUAL_TERMINAL_H_
#define VIRTUAL_TERMINAL_H_

#include "Std_macros.h"
#include "std_types.h"
#include "UART.h"

#define  BAUD_RATE 9600
void VirtTerm_vInit();
void VirtTerm_vSend(uint8 data) ;
void VirtTerm_vPrint(uint8* str);


#endif /* VIRTUAL_TERMINAL_H_ */