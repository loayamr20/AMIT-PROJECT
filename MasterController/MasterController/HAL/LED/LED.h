/*
 * LED.h
 *
 * Created: 11/21/2020 7:51:46 PM
 *  Author: Loay
 */ 


#ifndef LED_H_
#define LED_H_
#include "FrameWork/Framework.h"
#include "MCAL/DIO/DIO.h"

typedef struct{
	PORTS PORT;			
	uint8 PIN_NUM;
	}LED;

void LED_vInit(LED * led,PORTS PORT,uint8 PIN_NUM);
void LED_vTurnOn(LED * led);
void LED_vTurnOFF(LED * led);
void LED_vToggle(LED * led);

#endif /* LED_H_ */