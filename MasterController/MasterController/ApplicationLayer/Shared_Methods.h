/*
 * Shared_Methods.h
 *
 * Created: 12/17/2020 4:23:59 PM
 *  Author: Loay
 */ 


#ifndef SHARED_METHODS_H_
#define SHARED_METHODS_H_
#include "MCAL/UART/UART.h"
#include "HAL/LCD/LCD.h"


static void Uart_GetString(uint8 * str,uint8 MaxLength,boolean HIDE_ON_WRITE,boolean NUMIRC_ONLY)
{
	//Init arry with 0
	uint8 index = 0;
	uint8 val = 0;
	for(index = 0;index<MaxLength;index++)
	{
		str[index] = 0;
	}
	index = 0;
	while ((val != 0x0D)) // while Enter KeyCode 0x0D -> Not pressed and We have at least 1 Character written to UNAME
	{
		val = UART_Read_Wait();
		if (val == 0x0D) // if it is Enter key do Nothing
		{
			if (index == 0) // if no other char is add
			{
				val = 0; // reset val to not exit loop
			}
		}
		else if (val == 0x08) //backspace KeyCode -> means we Delete Last value
		{
			if (index > 0) // We have at least 1 Character written to UNAME
			{
				
				index -= 1; //Go back With Index by 1 char
				LCD_DeleteLast();
				str[index] =0;
			}
		}else{
			if (index < MaxLength)
			{
				str[index] =  val;
				index++;
				if (HIDE_ON_WRITE)
				{
					LCD_HIDE_Last();
				}
				LCD_vSendData(val);
			}
		}
	}
}





#endif /* SHARED_METHODS_H_ */