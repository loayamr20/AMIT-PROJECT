/*
 * LCD.h
 *
 * Created: 11/21/2020 11:57:34 PM
 *  Author: Loay
 *	Need to continue More
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "FrameWork/Framework.h"
#include "MCAL/DIO/DIO.h"

typedef enum
{
	clearScreen,
	Apend
}PrintType;

typedef enum
{
	Cursor_On = 0x0E,
	Cursor_OFF = 0x0C,
	Cursor_Blinking = 0x0F,
}CursorStates;

void LCD_vSendCMD(uint8 cmd);
void LCD_vInit(PORTS dataPort,PORTS Cntrl_Port,uint8 RS_pin,uint8 RW_pin,uint8 EN_pin);
void LCD_vSendData(uint8 Data);
void LCD_vPrint(uint8 * data,PrintType Method);
void LCD_vClearScreen();
void LCD_CursorState(CursorStates State);
void LCD_vMoveCursor(uint8 Row,uint8 Col);
void LCD_PrintNumber(uint16 N,boolean asci_autoshift);
void LCD_vMoveCursorLeft();
void LCD_vMoveCursorRight();
void LCD_DeleteLast();
void LCD_HIDE_Last();
#endif /* LCD_H_ */