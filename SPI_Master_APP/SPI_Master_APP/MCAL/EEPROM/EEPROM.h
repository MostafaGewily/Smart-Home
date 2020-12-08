/*
 * EEPROM.h
 *
 * Created: 11/9/2020 3:01:17 AM
 *  Author: ENG Mostafa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "Std_macros.h"

void EEPROM_vWrite(uint16 address, uint8 data) ;
uint8 EEPROM_u8Read(uint16 address);

#endif /* EEPROM_H_ */