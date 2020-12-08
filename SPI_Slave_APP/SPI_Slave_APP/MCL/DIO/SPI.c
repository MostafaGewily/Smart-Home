/*
 * SPI.c
 *
 * Created: 11/27/2020 10:18:20 AM
 *  Author: ENG Mostafa
 */ 
#include "SPI.h"
#define F_CPU 16000000UL
void SPI_vInit_Master()
{
	// Configure Master or Slave
	SET_BIT(SPCR,MSTR);
	// Configure Speed /128
	SET_BIT(SPCR,SPR0);
	SET_BIT(SPCR,SPR1); 
	// Configure MOSI, SS, SCK to be out
	SET_BIT(DDRB,SS);
	SET_BIT(DDRB,MOSI);
	SET_BIT(DDRB,SCK);
	// Put SS_PIN HIGH --> as i don't need to select slave now
	SET_BIT(PORTB,SS); 
	// Enable SPI peripheral
	SET_BIT(SPCR,SPE); 
}
void SPT_MasterTramsimt(uint8 data)
{
	// Enable SS to send data to slave, ss = 0
	CLR_BIT(PORTB,SS);
	// Put data to SPDR
 	SPDR = data ;
	// Check Transmission is done
	while (READ_BIT(SPSR,SPIF) == 0 )
	{
		// wait
	}
	// close SS -- > ss = 1 ;
	SET_BIT(PORTB,SS);
}
void SPI_vInit_Slave()
{
	// Configure Slave
	CLR_BIT(SPCR,MSTR);
	// Enable SPI
	SET_BIT(SPCR,SPE);
	// Set DDR for MISO
	SET_BIT(DDRB,MISO);
}
uint8 SPI_u8SlaveReceive()
{
	// Check if transmission is finished 
	   while (READ_BIT(SPSR,SPIF) == 0 )
	   {
		   // wait
	   }
	
	// Receive Data 
	 return SPDR ;
}