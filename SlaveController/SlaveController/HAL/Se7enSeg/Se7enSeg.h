/*
 * LED.h
 *
 * Created: 11/21/2020 7:51:46 PM
 *  Author: Loay
 */ 


#ifndef SEG_H_
#define SEG_H_
#include "FrameWork/Framework.h"
#include "MCAL/DIO/DIO.h"

typedef struct{
	PORTS PORT;
	uint8 PIN_NUM_1;
	uint8 PIN_NUM_2;
	uint8 PIN_NUM_3;
	uint8 PIN_NUM_4;
}SevenSeg_BCD;
void Seg_vInit(SevenSeg_BCD * seg,PORTS PORT,uint8 P1,uint8 P2,uint8 P3,uint8 P4);
void Seg_vDisplaySingle(SevenSeg_BCD * seg,uint8 Data);
void Seg_vDisplayDual(SevenSeg_BCD * seg_units,SevenSeg_BCD * Seg_Tens,uint8 Data);
#endif /* SEG_H_ */