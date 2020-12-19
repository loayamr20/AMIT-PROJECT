/*
 * UART.h
 *
 * Created: 11/21/2020 10:38:12 AM
 *  Author: Loay
 */ 


#ifndef UART_H_
#define UART_H_
#include "FrameWork/Framework.h"

void UART_vInit(uint32 Baudrate);
void UART_vSend(uint8 Data);
uint8 UART_Read();
uint8 UART_RECIVED_DATA();

uint8 UART_Read_Wait();


#endif /* UART_H_ */