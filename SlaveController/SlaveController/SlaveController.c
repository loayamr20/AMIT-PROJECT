/*
* SlaveController.c
*
* Created: 12/05/2020 6:50:39 PM
*  Author: Loay
*/

#include "FrameWork/Framework.h"
#include "HAL/LED/LED.h"
#include "HAL/Se7enSeg/Se7enSeg.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/SPI/SPI.h"

volatile uint8 AC_On_Threshold = 27;
volatile uint8 AC_OFF_threshold = 24;

LED Room1,Room2,AC_Unit;
SevenSeg_BCD Tens_Seg,Units_Seg;

/* proto-Types */
void AC_Check();

int main(void)
{
	/* SPI initialize using interrupt */
	SPI_Init_Slave_interrupt();
	/* LED Initialize (as Rooms) */
	LED_vInit(&Room1,PORT_D,7);
	LED_vInit(&Room2,PORT_D,6);
	LED_vInit(&AC_Unit,PORT_D,5);
	/* Seven segment Initialize */
	Seg_vInit(&Tens_Seg,PORT_C,4,5,6,7);
	Seg_vInit(&Units_Seg,PORT_C,0,1,2,3);
	/* ADC for Temp sensor Initialize */
	ADC_vInit(ADC_Scale_128,verf_Internal);
	
	
	/* main Code */
	Seg_vDisplayDual(&Units_Seg, &Tens_Seg ,AC_OFF_threshold);
	while(1)
	{
		/*Check AC state*/
		AC_Check();
		/* Delay to reduce CPU utilization */
		_delay_ms(200);		
	}
	return 0;
}

void AC_Check()
{	
	/* the AC on = to desired value +3 to prevent fast on off on small temp changes */
	AC_On_Threshold = AC_OFF_threshold +3;
	/* Display Required value */
	Seg_vDisplayDual(&Units_Seg, &Tens_Seg ,AC_OFF_threshold);
	/* Get Sensor reading using ADC */
	uint8 Temp = ADC_to_Temp(ADC_u16Read(ADC_Channel0));
	/* decide if ac should be turned on or off */	
	if (Temp >= AC_On_Threshold)
	{
		LED_vTurnOn(&AC_Unit);
	}
	if (Temp <=AC_OFF_threshold)
	{
		LED_vTurnOFF(&AC_Unit);
	}
}

volatile boolean WaitCMD = TRUE;
volatile boolean WaitValue = TRUE;
volatile uint8 CMD = 0;
ISR(SPI_STC_vect)
{
	if (WaitCMD)
	{
		if (SPI_u8Slave_Read() == '*')
		{
			WaitCMD = FALSE;
			return;
		}
		uint8 dummy = SPI_u8Slave_Read();
		return;
	}
	if (WaitValue)
	{
		CMD = SPI_u8Slave_Read();
		WaitValue = FALSE;
		return;
	}
	uint8 val = SPI_u8Slave_Read();
	
	if (CMD == ROOM_CMD)
	{
		if (val == 1)
		{
			LED_vToggle(&Room1);
		}
		if (val == 2)
		{
			LED_vToggle(&Room2);
		}
	}else if (CMD == AC_CMD)
	{
		AC_OFF_threshold = val;
		if (val > 40)
		LED_vToggle(&Room2);
	}	
	WaitCMD = TRUE;
	WaitValue = TRUE;
}