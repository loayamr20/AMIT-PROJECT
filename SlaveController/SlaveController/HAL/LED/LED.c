/*
 * LED.c
 *
 * Created: 11/21/2020 7:51:38 PM
 *  Author: Loay
 */ 


#include "LED.h"

void LED_vInit(LED * led,PORTS PORT,uint8 PIN_NUM)
{
	led->PIN_NUM = PIN_NUM;
	led->PORT = PORT;
	DIO_vSetPinDirection(PORT,PIN_NUM,DIO_OUTPUT);
}

void LED_vTurnOn(LED * led)
{
	DIO_vWritePin(led->PORT,led->PIN_NUM,DIO_HIGH);	
}

void LED_vTurnOFF(LED * led)
{
	DIO_vWritePin(led->PORT,led->PIN_NUM,DIO_LOW);
}

void LED_vToggle(LED * led)
{
	DIO_vTogglepin(led->PORT,led->PIN_NUM);
}