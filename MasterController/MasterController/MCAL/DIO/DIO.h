/*
 * DIO.h
 *
 * Created: 11/21/2020 6:10:18 PM
 *  Author: Loay
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "FrameWork/Framework.h"

#define PORT(X) (* Get_PORT(X))
#define DDR(X) (* Get_PORT(X))
#define PIN(X) (* Get_PORT(X))

typedef enum{
	DIO_INPUT = 0x00,
	DIO_OUTPUT = 0xFF,
	}DIO_Directions;

typedef enum{
	DIO_LOW = 0,
	DIO_HIGH = 1,
}DIO_Values;

typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	}PORTS;

typedef enum{
	DIO_LEFT_MASK,
	DIO_RIGHT_MASK,
	}MASK;

void DIO_vSetPinDirection(PORTS port,uint8 PIN_NUM,DIO_Directions Direction);
void DIO_vWritePin(PORTS port,uint8 PIN_NUM,DIO_Values Value);
DIO_Values DIO_ReadPin(PORTS port,uint8 PIN_NUM);
void DIO_vTogglepin(PORTS port, uint8 PIN_NUM);
void DIO_vSet_PORT_Direction(PORTS port,DIO_Directions Direction);
void DIO_vWrite_PORT(PORTS port,uint8 value);
DIO_Directions DIO_GetPinDirection(PORTS port,uint8 PIN_NUM);
uint8_t volatile * Get_PORT(PORTS port);
uint8_t volatile * Get_PIN(PORTS port);
uint8_t volatile * Get_DDR(PORTS port);
#endif /* DIO_H_ */