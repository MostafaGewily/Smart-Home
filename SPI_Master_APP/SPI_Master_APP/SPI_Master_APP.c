/*
 * SPI_Master_APP.c
 *
 * Created: 11/27/2020 10:15:28 AM
 *  Author: ENG Mostafa
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include "util/delay.h"
#include "SPI.h"
#include "LCD.h"
#include "Virtual_Terminal.h"
#include "EEPROM.h"
#include "LED.h"
#include "Timer.h"
#define START_ADDRESS 0x05
#define COUNTER_ADDRESS 0x06
static uint16 PASSWORD_ADDRESSES[4] ={0x01,0x02,0x03,0x04};
volatile uint8 DataReceived = 0;
volatile uint8 RxData = 0;
volatile uint8 count = 0;
int main(void)
{
	/* ******************************* Variables *********************************** */
	volatile uint8 i=0,TxDATA,state='N' ;
	/* ************************ Enable Global interrupt ***************************** */
	sei();
	/* ************************ Init MASTER ***************************** */
	SPI_vInit_Master();
    /* ************************ LCD ***************************** */ 
	LCD_vInit();
	/* ************************ LED ***************************** */
	LED_vInit();
	/* ************************ Virtual Terminal ***************************** */
	VirtTerm_vInit();
	/* ************************ Timer0 ***************************** */
	Timer0_vInit();
    /* ************************ Code ***************************** */ 
	/* *********************** Check Password ************************************** */
	                           /* FIRST TIME */
	              if ( EEPROM_u8Read(START_ADDRESS) == 0xff )
	              {
		              LCD_vCleanScreen();
		              LCD_vPrintData("Enter New Pass: ") ;
		              LCD_vMoveCursor(SECOND_ROW,0);
		              while(i<4)
		              {
			              if (DataReceived == 1 )
			              {
				              DataReceived = 0 ;
				              EEPROM_vWrite(PASSWORD_ADDRESSES[i],RxData);
				              LCD_vSendData('*');
				              i++;
			              }
		              }
		              EEPROM_vWrite(START_ADDRESS,0xEE);
		              EEPROM_vWrite(COUNTER_ADDRESS,0x00);
	              }
	              /* Try To open Home */
	              else
	              {
		              // check error password
		              uint8 c=0 ;
		              LCD_vCleanScreen();
		              LCD_vPrintData("Enter your Pass: ") ;
		              LCD_vMoveCursor(SECOND_ROW,0);
		              while(i<4)
		              {
			              // BLOCK
			              if (EEPROM_u8Read(COUNTER_ADDRESS) == 3 )
			              {
				              /* LED_ON */
							  PORTD |=(1<<3);
				              /* Display BLOCK */
				              LCD_vCleanScreen();
				              LCD_vPrintData("BLOCK");
				              /* Wait */
				              _delay_ms(5000);
				              /* Start again to read the password */
				              i = 0 ;
				              // Counter of error trials start again count from 0 to 3
				              EEPROM_vWrite(COUNTER_ADDRESS,0x00);
				              /* LED_OFF */
							  PORTD &=~(1<<3);
				              LCD_vCleanScreen();
				              LCD_vPrintData("Enter your Pass: ") ;
				              LCD_vMoveCursor(SECOND_ROW,0);
			              }
			              // READ PASSWORD
			              if (DataReceived == 1 )
			              {
				              DataReceived = 0 ;
				              if ( EEPROM_u8Read(PASSWORD_ADDRESSES[i]) == RxData)
				              {
					              
				              }
				              else
				              {
					              c++;
				              }
				              LCD_vSendData('*');
				              i++;
			              }
			              // CHECK IS THE PASSWORD WRONG ?
			              if ( i == 4 && c != 0)
			              {
				              LCD_vCleanScreen();
				              LCD_vPrintData("Error Pass");
				              _delay_ms(1000);
				              LCD_vCleanScreen();
				              LCD_vPrintData("Renter pass: ") ;
				              LCD_vMoveCursor(SECOND_ROW,0);
				              uint8 temp = EEPROM_u8Read(COUNTER_ADDRESS) ;
				              EEPROM_vWrite(COUNTER_ADDRESS,temp+1);
				              i = 0 ;
				              c = 0 ;
			              }
		              } // end while
		              
	              } // end else
				  LCD_vCleanScreen();
				  LCD_vPrintData("ENTER");
   /* ************************* start menu ******************************* */
	              _delay_ms(1000);
	              VirtTerm_vPrint("Welcome Sir \r");
	              VirtTerm_vPrint("0:Room0 \r");
	              VirtTerm_vPrint("1:Room1 \r");
	              VirtTerm_vPrint("2:Air Conditions \r");         
 /* *********************** While loop ************************************** */
    while(1)
    {
                   //TODO:: Please write your application code 
	   /* ********************** READ THE REQUIRED TASK *************************** */
		if (DataReceived == 1 )
		{
            count = 0;
   			DataReceived = 0 ;
			TxDATA = RxData ;
			VirtTerm_vSend(TxDATA);
			switch (TxDATA)
			{
			  case '0' :
			  VirtTerm_vPrint(" : Toggle Romm0\r");
			  SPI_vMasterTramsimt(TxDATA);
			  break;
			  case '1' :
			  VirtTerm_vPrint(" : Toggle Romm1\r");
			  SPI_vMasterTramsimt(TxDATA);
			  break;
			  case '2' :
			  VirtTerm_vPrint(" : ON/OFF Air conditioner\r");
			  SPI_vMasterTramsimt(TxDATA);
			  VirtTerm_vPrint("Enter Temp(2-digit):");
			  i=0;
			  while(i<2)
			  {
				 if (DataReceived == 1 )
				 {
					 DataReceived = 0 ;
					 TxDATA = RxData ;
					 VirtTerm_vSend(TxDATA);
					 SPI_vMasterTramsimt(TxDATA);
					 i++;
				 }					  
			  }
			  SPI_vMasterTramsimt("\r");
			  break;
			  default:
			  VirtTerm_vPrint(" : wrong entry\r");
			  SPI_vMasterTramsimt(TxDATA);
			  break; 	
			} /* END SWITCH CASE */
		} /* END REQUIRED TASK */
		else 
		{
		 if ( count == 500)
		    {
				LCD_vPrintData("EXIT");
				return 0;
			}	
		}					  
    } /* END WHILE(1) */
} /* END MAINE */

ISR(USART_RXC_vect)
{
	DataReceived = 1 ;
	RxData = UDR; 
}
ISR(TIMER0_COMP_vect)
{
	// every 10ms
	count++;
}