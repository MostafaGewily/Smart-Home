/*
 * SPI_Slave_APP.c
 *
 * Created: 11/27/2020 11:14:05 AM
 *  Author: ENG Mostafa
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "SPI.h"
#include "ADC.h"
#include "LED.h"
#include "LCD.h"
volatile uint16 result = 0 ;
volatile uint8 flag = 0 ;
volatile uint8 state ;
int main(void)
{
	/* ******************************* Variables *********************************** */
	volatile uint8 RxData,ReTemp,MeTemp;
	/* ************************ Enable Global interrupt ***************************** */
	sei();
	/* ************************ Init Slave ***************************** */
	SPI_vInit_Slave();
	/* ************************ LED ***************************** */
	LED_vInit();
	/* ************************ LCD ***************************** */
	LCD_vInit();
	/* ************************ ADC ***************************** */
	ADC_vInit() ;
	ADC_vStartConversion();	// ready to read value
	/* ************************ Code ***************************** */
    while(1)
    {	
                   //TODO:: Please write your application code 
	  /* **************************** RECEIVED TASK ****************************** */	 
			RxData = SPI_u8SlaveReceive();
			switch (RxData)
			{
				case '0' :
				// Toggle Room0
				PORTD ^= (1<<0);
				break;
				case '1' :
				// Toggle Room1
				PORTD ^= (1<<1);
				break;
				case '2' :
				// ON/OFF Air Conditioner
				LCD_vCleanScreen();
				LCD_vPrintData("ReTemp: ");
				state = 'n' ;
				while ( state == 'n' )
				{
					RxData = SPI_u8SlaveReceive();
					LCD_vSendData(RxData);
					ReTemp = RxData*10 ;
				}
				state= 'n';
				while ( state == 'n' )
				{
					RxData = SPI_u8SlaveReceive();
					LCD_vSendData(RxData);
					ReTemp = ReTemp + RxData ;
				}	
				state = 'n';
				LCD_vMoveCursor(SECOND_ROW,0);
				LCD_vPrintData("MeTemp: ")	;			
					if (flag==1)
					{
						MeTemp = result;
						uint8 show;
						while(MeTemp/10 != 0)
						{
							show = MeTemp/10;
							MeTemp = MeTemp%10;
							LCD_vSendData(show+'0');
						}
						LCD_vSendData(MeTemp+'0');
						flag = 0 ;
					}
					MeTemp = result;
					if(MeTemp > ReTemp)
					{
						PORTD |=(1<<2);
					}
					else if (MeTemp < ReTemp)
					{
						PORTD &=~(1<<2);
					}
					else
					{
						// No Change 
					}
				break;
				default:
				// Wrong Entry
				break;
			} /* END SWICH CASE */				
    } /* END WHILE(1) */
} /* END MAIN */
ISR(ADC_vect)
{
	result = (uint16)ADCL ;
	result |= (uint16) (ADCH<<8);
	result *= 0.5;
	flag = 1 ;
	ADC_vStartConversion();
}