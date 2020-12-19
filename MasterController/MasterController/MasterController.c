/*
* MasterController.c
*
* Created: 12/05/2020 6:49:51 PM
*  Author: Loay
*/
#include "FrameWork/Framework.h"
#include "ApplicationLayer/user_account.h"
#include "MCAL/SPI/SPI.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/Timer/Timer.h"

void WelcomeMSG()
{
	LCD_vPrint("Welcome To your",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("Smart Home^_^",Apend);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vPrint(".",Apend);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vPrint(".",Apend);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vPrint(".",Apend);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vClearScreen();
}

void RoomMenu()
{
	LCD_vPrint("Choose Room",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("1)Room1 2)Room 2",Apend);
	uint8 Opt2 = UART_Read_Wait();
	switch (Opt2)
	{
		case '1':
		SPI_SendCMD(ROOM_CMD,1);
		LCD_vPrint("all done",clearScreen);
		LCD_vMoveCursor(1,0);
		LCD_vPrint("Enjoy",Apend);
		_delay_ms(SHOW_STRING_DELAY);
		break;
		case '2':
		SPI_SendCMD(ROOM_CMD,2);
		LCD_vPrint("all done",clearScreen);
		LCD_vMoveCursor(1,0);
		LCD_vPrint("Enjoy",Apend);
		_delay_ms(SHOW_STRING_DELAY);
		break;
		default:
		LCD_vPrint("wrong input",clearScreen);
		_delay_ms(SHOW_STRING_DELAY);
		break;
	}
}

void ACMenu()
{
	LCD_vPrint("set AC temp:",clearScreen);
	LCD_vMoveCursor(1,0);
	uint8 degree[3]; // the extra 1 is for null terminator
	Uart_GetString(degree,2,FALSE,TRUE);
	uint8 val = (uint8)atoi(degree);	
	SPI_SendCMD(AC_CMD,val);
	LCD_vPrint("temp set",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("Enjoy",Apend);
	_delay_ms(SHOW_STRING_DELAY);
}

void MainMenu()
{
	LCD_vPrint("Choose,Option",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("1)Room 2)AC unit",Apend);
	uint8 Opt = UART_Read_Wait();
	switch (Opt)
	{
		case '1':
		RoomMenu();
		break;
		case '2':
		ACMenu();
		break;
		default:
		/* Your code here */
		break;
	}
}

int main(void)
{
	/* Initialization */
	//Timer must be before sei  ??
	Timer0_v1msInit();
	UART_vInit(9600);
	SPI_Init_Master();
	LCD_vInit(PORT_C,PORT_D,7,6,5);
	LCD_CursorState(Cursor_OFF);
	LED_vInit(&BlockLED,PORT_A,0);
	sei();
	
	
	/* Main Code Logic */
	//WelcomeMSG();
	user_vLogin();
	LCD_vPrint("Welcome !",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_vPrint(current_user.UserName,Apend);
	_delay_ms(SHOW_STRING_DELAY);
	while(1)
	{
		MainMenu();
	}
	
}