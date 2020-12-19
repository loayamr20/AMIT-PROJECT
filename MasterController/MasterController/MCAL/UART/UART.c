/*
* UART.c
*
* Created: 11/21/2020 10:38:01 AM
*  Author: Loay
*/
#include "UART.h"


static volatile char UART_DATA = 0;
static volatile uint8 urt_RECIVED_DATA = 0;

void UART_vInit(uint32 Baudrate)
{
	uint16 ubrr;
	
	ubrr = ((F_CPU/(16*Baudrate)) - 1);
	
	UBRRL = (uint8) ubrr;
	UBRRH = (uint8) (ubrr >> 8);
	
	UCSRC = (1 << URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UCSRB = (1<<RXCIE);
	
	sei();
	
	UCSRB |= (1<<TXEN) | (1<<RXEN) ;
}

void UART_vSend(uint8 Data)
{
	/* Wait For Data To Be Sent If there is Data on Buffer */
	while ((UCSRA & (1<<UDRE)) == 0)  //(GET_BIT(UCSRA,UDRE) == 0)
	{
		/* waiting */
	}
	
	/* writing Data to Buffer */ 
	
	UDR = Data;
	
	
}

uint8 UART_Read_Wait(){
	while(urt_RECIVED_DATA == 0)
	{
		/* Waiting */
	}
	return UART_Read();
}

uint8 UART_Read()
{
	urt_RECIVED_DATA = 0;
	return UART_DATA;
}

uint8 UART_RECIVED_DATA()
{	
	return urt_RECIVED_DATA;
}

ISR(USART_RXC_vect)
{	
	UART_DATA = UDR;
	urt_RECIVED_DATA = 1;
}