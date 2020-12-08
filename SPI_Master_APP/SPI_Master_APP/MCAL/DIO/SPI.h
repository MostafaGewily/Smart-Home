/*
 * SPI.h
 *
 * Created: 11/27/2020 10:18:34 AM
 *  Author: ENG Mostafa
 */ 

#ifndef SPI_H_
#define SPI_H_

#include "Std_macros.h"
#include "std_types.h"
#include <avr/io.h>

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

void SPI_vInit_Master();
void SPI_vMasterTramsimt(uint8 data);

void SPI_vInit_Slave();
uint8 SPI_u8SlaveReceive();
#endif /* SPI_H_ */