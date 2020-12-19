/*
* DIO.c
*
* Created: 11/21/2020 6:10:26 PM
*  Author: Loay
*/
#include "DIO.h"

void DIO_vSetPinDirection(PORTS port,uint8 PIN_NUM,DIO_Directions Direction)
{		
	uint8_t volatile * DDR;
	switch (port)
	{
		case PORT_A:
			DDR = &DDRA;
			break;
		case PORT_B:
			DDR = &DDRB;
			break;
		case PORT_C:
			DDR = &DDRC;
			break;
		case PORT_D:
			DDR = &DDRD;
			break;
		default:
			return;	
		break;
	}
	
	switch (Direction)
	{
		case DIO_INPUT:		
		CLR_BIT(*DDR,PIN_NUM);
		break;
		case DIO_OUTPUT:
		SET_BIT(*DDR,PIN_NUM);
		break;
		default:
		/* Your code here */
		break;
	}
	
}

void DIO_vWritePin(PORTS port,uint8 PIN_NUM,DIO_Values Value)
{
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &PORTA;
		break;
		case PORT_B:
		PORT = &PORTB;
		break;
		case PORT_C:
		PORT = &PORTC;
		break;
		case PORT_D:
		PORT = &PORTD;
		break;
		default:
		return;
		break;
	}
	
	switch (Value)
	{
		case DIO_HIGH:
		SET_BIT(*PORT,PIN_NUM);
		break;
		case DIO_LOW:
		CLR_BIT(*PORT,PIN_NUM);
		break;
		default:
		/* Your code here */
		break;
	}
}

DIO_Values DIO_ReadPin(PORTS port,uint8 PIN_NUM)
{
	uint8 volatile * PIN;
	switch (port)
	{
		case PORT_A:
		PIN = &PINA;
		break;
		case PORT_B:
		PIN = &PINB;
		break;
		case PORT_C:
		PIN = &PINC;
		break;
		case PORT_D:
		PIN = &PIND;
		break;
		default:
		return 0;
		break;
	}
	return GET_BIT(*PIN,PIN_NUM);
}

void DIO_vTogglepin(PORTS port, uint8 PIN_NUM){	
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &PORTA;
		break;
		case PORT_B:
		PORT = &PORTB;
		break;
		case PORT_C:
		PORT = &PORTC;
		break;
		case PORT_D:
		PORT = &PORTD;
		break;
		default:
		return;
		break;
	}
	TOGGLE_BIT(* PORT,PIN_NUM);
}

void DIO_vSet_PORT_Direction(PORTS port,DIO_Directions Direction)
{
	uint8_t volatile * DDR;
	switch (port)
	{
		case PORT_A:
		DDR = &DDRA;
		break;
		case PORT_B:
		DDR = &DDRB;
		break;
		case PORT_C:
		DDR = &DDRC;
		break;
		case PORT_D:
		DDR = &DDRD;
		break;
		default:
		return;
		break;
	}
	* DDR = Direction;	
}

void DIO_vWrite_PORT(PORTS port,uint8 value)
{
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &PORTA;
		break;
		case PORT_B:
		PORT = &PORTB;
		break;
		case PORT_C:
		PORT = &PORTC;
		break;
		case PORT_D:
		PORT = &PORTD;
		break;
		default:
		return;
		break;
	}
	* PORT = value;
}

DIO_Directions DIO_GetPinDirection(PORTS port,uint8 PIN_NUM)
{
	uint8_t volatile * DDR;
	switch (port)
	{
		case PORT_A:
		DDR = &DDRA;
		break;
		case PORT_B:
		DDR = &DDRB;
		break;
		case PORT_C:
		DDR = &DDRC;
		break;
		case PORT_D:
		DDR = &DDRD;
		break;
		default:
		return 0;
		break;
	}	
	if (GET_BIT(* DDR,PIN_NUM))
	{
		return DIO_OUTPUT;
	}else{
		return DIO_INPUT;
	}
}

void DIO_vWrite_PORT_Masked(PORTS port,uint8 value,MASK mask)
{
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &PORTA;
		break;
		case PORT_B:
		PORT = &PORTB;
		break;
		case PORT_C:
		PORT = &PORTC;
		break;
		case PORT_D:
		PORT = &PORTD;
		break;
		default:
		return;
		break;
	}
	
	switch (mask)
	{
		case DIO_LEFT_MASK:
		*PORT &= 0x0F;	/* clear bits where we will right */	
		*PORT |= (value & 0xF0);  /* write the bits to where we need */
		break;
		case DIO_RIGHT_MASK:
		*PORT &= 0xF0;	/* clear bits where we will right */
		*PORT |= (value & 0x0F);  /* write the bits to where we need */
		break;
		default:
		/* Your code here */
		break;
	}
}

uint8_t volatile * Get_PORT(PORTS port)
{
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &PORTA;
		break;
		case PORT_B:
		PORT = &PORTB;
		break;
		case PORT_C:
		PORT = &PORTC;
		break;
		case PORT_D:
		PORT = &PORTD;
		break;
		default:
		break;
	}
	return PORT;
}

uint8_t volatile * Get_DDR(PORTS port)
{
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &DDRA;
		break;
		case PORT_B:
		PORT = &DDRB;
		break;
		case PORT_C:
		PORT = &DDRC;
		break;
		case PORT_D:
		PORT = &DDRD;
		break;
		default:
		break;
	}
	return PORT;
}

uint8_t volatile * Get_PIN(PORTS port)
{
	uint8 volatile * PORT;
	switch (port)
	{
		case PORT_A:
		PORT = &PINA;
		break;
		case PORT_B:
		PORT = &PINB;
		break;
		case PORT_C:
		PORT = &PINC;
		break;
		case PORT_D:
		PORT = &PIND;
		break;
		default:
		break;
	}
	return PORT;
}

