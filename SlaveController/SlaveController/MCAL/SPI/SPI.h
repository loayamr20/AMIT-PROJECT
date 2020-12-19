/*
 * SPI.h
 *
 * Created: 11/27/2020 10:11:03 AM
 *  Author: Loay
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "FrameWork/Framework.h"
#include "MCAL/DIO/DIO.h"


#define ROOM_CMD 0
#define AC_CMD 1

void SPI_Init_Master(void);

void SPI_Init_Slave(void);

void SPI_Master_Transmit(uint8 Data);

uint8 SPI_u8Slave_Read();

void SPI_Init_Slave_interrupt();

uint8 SPI_GetCMD();
void SPI_SEND_STRING(uint8 * str);
void SPI_SendCMD(uint8 cmd,uint8 value);

#endif /* SPI_H_ */