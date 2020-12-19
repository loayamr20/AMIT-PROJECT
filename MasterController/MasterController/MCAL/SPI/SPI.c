/*
 * SPI.c
 *
 * Created: 11/27/2020 10:10:53 AM
 *  Author: Loay
 */ 
#include "SPI.h"

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

/*
     as SPI Protocol 
	 
	 CMD ToggelRoom ID          0 1
	 SET Required_Temp  value   1 27
	 
	 
	 *0 1 >> Toggel room 1
	 *1 22 >> Set temp to 22
	 
*/

#define START_CMD "*"

void SPI_Init_Master(void)
{
	/* Config Master / Slave */
	SET_BIT(SPCR,MSTR);	
	/* config clock speed 128 for Atmega32  */
	SET_BIT(SPCR,SPR0);
	SET_BIT(SPCR,SPR1);
	/* config DDR MOSI/SS/SCK */
	DIO_vSetPinDirection(PORT_B,SS,DIO_OUTPUT);
	DIO_vSetPinDirection(PORT_B,MOSI,DIO_OUTPUT);
	DIO_vSetPinDirection(PORT_B,SCK,DIO_OUTPUT);
	/* PUT SS High (Turn Off Slave) */
	DIO_vWritePin(PORT_B,SS,DIO_HIGH);
	/* Enable SPI peripheral */
	SET_BIT(SPCR,SPE);	
}

void SPI_Init_Slave(void)
{
	/* Config Master / Slave */
	CLR_BIT(SPCR,MSTR);
	/* config DDR MISO */
	DIO_vSetPinDirection(PORT_B,MISO,DIO_OUTPUT);
	/* Enable SPI peripheral */
	SET_BIT(SPCR,SPE);
}

void SPI_Master_Transmit(uint8 Data)
{
	/* Enable SS */
	DIO_vWritePin(PORT_B,SS,DIO_LOW);
	/* PUT Data to SPDR */
	SPDR = Data;
	/* Check transmission is Done */
	while (GET_BIT(SPSR,SPIF) == 0)
	{
		/* when finished SPIF is set to 1 */
	}
	/* Disable SS */
	DIO_vWritePin(PORT_B,SS,DIO_HIGH);
	_delay_ms(30);
}

uint8 SPI_u8Slave_Read()
{
	while(GET_BIT(SPSR,SPIF) == 0)
	{
		/* wait For Data */
	}
	return SPDR;
}

uint8 SPI_GetCMD()
{
	if (SPI_u8Slave_Read() == '*')
		if (SPI_u8Slave_Read() == '*')
		{
			return SPI_u8Slave_Read();
		}
}

void SPI_SEND_STRING(uint8 * str)
{
	while(*str)
	{
		SPI_Master_Transmit(*str++);
	}
}

void SPI_SendCMD(uint8 cmd,uint8 value)
{
	SPI_SEND_STRING(START_CMD);
	SPI_Master_Transmit(cmd);
	SPI_Master_Transmit(value);
}

