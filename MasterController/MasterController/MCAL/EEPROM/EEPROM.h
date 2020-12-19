/*
 * EEPROM.h
 *
 * Created: 11/07/2020 11:29:28 AM
 *  Author: Loay
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "FrameWork/Framework.h"
//future work >  Note :  as a Driver  use Void * as Type with size as paramter and write as loop;

void EEPROM_vWrite(uint16 address,uint8 value);
uint8 EEPROM_u8Read(uint16 address);
void EEPROM_ReadSTR(uint16 address,uint8 * str,uint8 Length);
void EEPROM_WriteSTR(uint16 address,uint8 * str,uint8 Length);

#endif /* EEPROM_H_ */