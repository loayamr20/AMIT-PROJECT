/*
* LED.c
*
* Created: 11/21/2020 7:51:38 PM
*  Author: Loay
*/


#include "Se7enSeg.h"
#define USING_BCD_DECODER
#ifdef USING_BCD_DECODER


void Seg_vInit(SevenSeg_BCD * seg,PORTS port,uint8 P1,uint8 P2,uint8 P3,uint8 P4)
{
	seg->PIN_NUM_1 = P1;
	seg->PIN_NUM_2 = P2;
	seg->PIN_NUM_3 = P3;
	seg->PIN_NUM_4 = P4;
	seg->PORT = port;
	DIO_vSetPinDirection(seg->PORT,seg->PIN_NUM_1,DIO_OUTPUT);
	DIO_vSetPinDirection(seg->PORT,seg->PIN_NUM_2,DIO_OUTPUT);
	DIO_vSetPinDirection(seg->PORT,seg->PIN_NUM_3,DIO_OUTPUT);
	DIO_vSetPinDirection(seg->PORT,seg->PIN_NUM_4,DIO_OUTPUT);
}

void Seg_vDisplaySingle(SevenSeg_BCD * seg,uint8 Data)
{
	DIO_vWritePin(seg->PORT,seg->PIN_NUM_1,DIO_LOW);
	DIO_vWritePin(seg->PORT,seg->PIN_NUM_2,DIO_LOW);
	DIO_vWritePin(seg->PORT,seg->PIN_NUM_3,DIO_LOW);
	DIO_vWritePin(seg->PORT,seg->PIN_NUM_4,DIO_LOW);
	
	PORT(seg->PORT) |= (Data <<seg->PIN_NUM_1);
}
void Seg_vDisplayDual(SevenSeg_BCD * seg_units,SevenSeg_BCD * Seg_Tens,uint8 Data)
{
	if (Data> 100)
	{
		Data = 99;
	}
	if (Data< 0)
	{
		Data = 0;
	}
	uint8 unit = Data%10;
	if (unit > 9)
	{
		unit = 9;
	}

	Seg_vDisplaySingle(Seg_Tens,Data/10);
	Seg_vDisplaySingle(seg_units,unit);
}


#endif