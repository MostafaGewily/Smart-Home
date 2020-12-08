/*
 * EEPROM.c
 *
 * Created: 11/9/2020 3:01:02 AM
 *  Author: ENG Mostafa
 */ 
#include "EEPROM.h"
#include <avr/io.h>
void EEPROM_vWrite(uint16 address, uint8 data)
{
	while(READ_BIT(EECR,EEWE))
	{
	}
	// EEAR = address
	EEARH = (address>>8);
	EEARL = (char) address;
	// READ DATA
	EEDR = data;
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
}
uint8 EEPROM_u8Read(uint16 address)
{
	while(READ_BIT(EECR,EEWE))
	{
	}		
	// EEAR = address
	EEARH = (address>>8);
	EEARL = (char) address;
	SET_BIT(EECR,EERE);
	return EEDR;
	
}