/*
* EEPROM.c
*
* Created: 11/07/2020 11:29:17 AM
*  Author: Loay
*/
#include "EEPROM.h"



void EEPROM_vWrite(uint16 address,uint8 value)
{
	//Wait if EEPROM Busy
	while(GET_BIT(EECR,EEWE) == 1);
	EEARH = (char) (address >> 8);
	EEARL = (char) (address);
	EEDR = value;
	/* Set Master Write Enable */
	SET_BIT(EECR,EEMWE);
	/* Set Write Enable Within 4 Clocks To Actually Write */
	SET_BIT(EECR,EEWE);
}

uint8 EEPROM_u8Read(uint16 address)
{
	//Wait if EEPROM Busy
	while(GET_BIT(EECR,EEWE) == 1);
	EEARH = (char) (address >> 8);
	EEARL = (char) (address);
	SET_BIT(EECR,EERE);
	return EEDR;
}

void EEPROM_WriteSTR(uint16 address,uint8 * str,uint8 Length)
{
	uint8 i = 0;
	for (i = 0;i<Length;i++)
	{
		EEPROM_vWrite(address + i,str[i]);
	}
}

void EEPROM_ReadSTR(uint16 address,uint8 * str,uint8 Length)
{
	uint8 i = 0;
	for (i = 0;i<Length;i++)
	{
		str[i] = EEPROM_u8Read(address + i);
	}
}