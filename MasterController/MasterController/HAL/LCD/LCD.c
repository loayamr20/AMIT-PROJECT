/*
* LCD.c
*
* Created: 11/21/2020 11:57:25 PM
*  Author: Loay
*/

/*

LCD Operates as Follows :
1 - it is intialized using commands from dataSheet
2-	u choose the data type are u sending cmd or sending data to print
3-	u set the data on Port USB is connected to
4-	u send a falling Edge pulse by setting the enable bit to 1 then to 0

*/


#include "LCD.h"

/* LCD Commands */
#define ROW0 0x80
#define ROW1 0xC0



#define CLRSCR_CMD 0x01  /* Clear screen cmd */

#define BLINKCURSOR_CMD 0x0C /* BLINK cursor cmd */

#define CURSOR_LEFT 0x10
#define CURSOR_RIGHT 0x14

#define CURSOR_POINT_LEFT 0x04
#define CURSOR_POINT_RIGHT 0x06


#define SHIFT_LCD_RIGHT 0x1c
#define SHIFT_LCD_LIFT	0x18

uint8 RS,RW,EN;
PORTS DataPort,ControlPort;

uint8 CursorLocation = 0;

void AutoShiftScreen();
void LCD_vMoveCursorLeft();
void LCD_vMoveCursorRight();
void LCD_vShiftScreenLeft();
void LCD_vShiftScreenRight();

static void LCD_vSendFallingEdge()
{
	DIO_vWritePin(ControlPort,EN,DIO_HIGH); /* Write 1 to EN pin to start Falling Edge */
	_delay_ms(2);  /* wait a small amount of time to make sure bit it read by LCD */
	DIO_vWritePin(ControlPort,EN,DIO_LOW); /* Write 0 to EN pin to End Falling Edge */
	_delay_ms(1);  /* wait a small amount of time to make sure bit it read by LCD */
}

void LCD_vClearScreen()
{
	CursorLocation = 0;
	LCD_vSendCMD(CLRSCR_CMD); /* Clear Screen */
}

void LCD_vPrint(uint8 * data,PrintType Method)
{
	
	if (Method == clearScreen)
	{
		LCD_vSendCMD(CLRSCR_CMD); /* Clear Screen */
	}
	while(*data){
		LCD_vSendData(*data++);
		//_delay_ms(1);
	}
}

void LCD_CursorState(CursorStates State){
	LCD_vSendCMD(State);
}

void LCD_vMoveCursor(uint8 Row,uint8 Col){
	uint8 temp;
	switch (Row)
	{
		case 0:
		temp = ROW0 + Col;
		break;
		case 1:
		temp = ROW1 + Col;
		break;
		default:
		temp = ROW1 + Col;
		break;
	}
	LCD_vSendCMD(temp);
}

void LCD_vMoveCursorLeft(){
	LCD_vSendCMD(CURSOR_LEFT);
}

void LCD_vMoveCursorRight(){
	LCD_vSendCMD(CURSOR_RIGHT);
}

void LCD_vShiftScreenLeft(){
	LCD_vSendCMD(SHIFT_LCD_LIFT);
}

void LCD_vShiftScreenRight(){
	LCD_vSendCMD(SHIFT_LCD_RIGHT);
}

void AutoShiftScreen()
{
	CursorLocation++;
	if (CursorLocation > 16 && CursorLocation < 41)
	{
		LCD_vShiftScreenLeft();
	}
	if (CursorLocation == 41)
	{
		int i;
		for (i =0;i<16;i++)
		{
			LCD_vShiftScreenLeft();
		}
	}
	if (CursorLocation > 56)
	{
		LCD_vShiftScreenLeft();
	}
	if (CursorLocation > 80)
	{
		int i;
		for (i =0;i<16;i++)
		{
			LCD_vShiftScreenLeft();
		}
		CursorLocation = 0;
		LCD_vMoveCursor(0,0);
	}
}

void LCD_PrintNumber(uint16 N,boolean asci_autoshift)
{
	uint16 newN = reversDigits(N);
	while(newN >= 10)
	{
		uint16 temp = newN;
		while (temp >= 10)
		{
			temp /= 10;
		}
		if (asci_autoshift)
		{
			LCD_vSendData(temp + '0');
		}else{
			LCD_vSendData(temp);
		}
		newN /= 10;
	}
	if (asci_autoshift)
	{
		LCD_vSendData(newN + '0');
	}else{
		LCD_vSendData(newN);
	}
}

void LCD_DeleteLast()
{
	LCD_vMoveCursorLeft();
	LCD_vSendData(' ');
	LCD_vMoveCursorLeft();
}

void LCD_HIDE_Last()
{
	LCD_vMoveCursorLeft();
	LCD_vSendData('*');
	
}


#ifndef LCD_4_BIT  /* We Are in 8 bit mode - Not the AMIT KIT */

#define INIT_CMD 0x38   /* initialization cmd */

void LCD_vInit(PORTS dataPort,PORTS Cntrl_Port,uint8 RS_pin,uint8 RW_pin,uint8 EN_pin)
{
	DataPort = dataPort;
	ControlPort = Cntrl_Port;
	
	RS = RS_pin;
	RW = RW_pin;
	EN = EN_pin;
	
	DIO_vSet_PORT_Direction(DataPort,DIO_OUTPUT);  /* set the data port as output port */
	DIO_vSetPinDirection(ControlPort,RS,DIO_OUTPUT);  /* set RS pin as output */
	DIO_vSetPinDirection(ControlPort,RW,DIO_OUTPUT);  /* set RW pin as output */
	DIO_vSetPinDirection(ControlPort,EN,DIO_OUTPUT);  /* set EN pin as output*/
	
	DIO_vWritePin(ControlPort,RW,DIO_LOW);  /* Set LCD in Write Mode */
	
	LCD_vSendCMD(INIT_CMD);
	LCD_vSendCMD(CLRSCR_CMD);
	//LCD_vSendCMD(0x06);
}

void LCD_vSendCMD(uint8 cmd)
{
	DIO_vWrite_PORT(DataPort,cmd);  /* PUT Data On PORT */
	DIO_vWritePin(ControlPort,RS,DIO_LOW);	/* Set RS as 0 to Define it as Command */
	LCD_vSendFallingEdge(); /* Send a fallingEdge to LCD to make it read the CMD */
}

void LCD_vSendData(uint8 Data)
{
	DIO_vWrite_PORT(DataPort,Data);  /* PUT Data On PORT */
	DIO_vWritePin(ControlPort,RS,DIO_HIGH);	/* Set RS as 1 to Define it as Data */
	LCD_vSendFallingEdge(); /* Send a fallingEdge to LCD to make it read the CMD */
	//AutoShiftScreen();
}

#else  /* We Are in 4 bit mode - the AMIT KIT MODE */


#define INIT_CMD_1 0x33   /* initialization cmd 1*/
#define INIT_CMD_2 0x32   /* initialization cmd 2*/
#define INIT_CMD_3 0x28   /* initialization cmd 3*/

void LCD_vInit(PORTS dataPort,PORTS Cntrl_Port,uint8 RS_pin,uint8 RW_pin,uint8 EN_pin)
{
	DataPort = dataPort;
	ControlPort = Cntrl_Port;
	
	RS = RS_pin;
	RW = RW_pin;
	EN = EN_pin;
	
	DIO_vSet_PORT_Direction(DataPort,DIO_OUTPUT);  /* set the data port as output port */
	DIO_vSetPinDirection(ControlPort,RS,DIO_OUTPUT);  /* set RS pin as output */
	DIO_vSetPinDirection(ControlPort,RW,DIO_OUTPUT);  /* set RW pin as output */
	DIO_vSetPinDirection(ControlPort,EN,DIO_OUTPUT);  /* set EN pin as output*/
	
	DIO_vWritePin(ControlPort,RW,DIO_LOW);  /* Set LCD in Write Mode */
	
	LCD_vSendCMD(INIT_CMD_1); /* Initializations according to Data sheet */
	LCD_vSendCMD(INIT_CMD_2);
	LCD_vSendCMD(INIT_CMD_3);
	
	LCD_vSendCMD(CLRSCR_CMD);
	LCD_vSendCMD(BLINKCURSOR_CMD);
	
}

void LCD_vSendCMD(uint8 cmd)
{
	/* PUT Half Data On PORT */
	PORT(DataPort) &= 0x0F; /*clear where we Put data*/
	//* Get_PORT(DataPort) &= 0x0F; /*clear where we Put data*/
	PORT(DataPort) |= (cmd & 0xF0);	/* write our data */
	//* Get_PORT(DataPort) |= (cmd & 0xF0);	/* write our data */
	DIO_vWritePin(ControlPort,RS,DIO_LOW);	/* Set RS as 0 to Define it as Command */
	LCD_vSendFallingEdge(); /* Send a fallingEdge to LCD to make it read the CMD */
	
	/* PUT Other Half Data On PORT */
	PORT(DataPort) &= 0x0F; /*clear where we Put data*/
	PORT(DataPort) |= (cmd << 4); /* write our data */
	DIO_vWritePin(ControlPort,RS,DIO_LOW);	/* Set RS as 0 to Define it as Command */
	LCD_vSendFallingEdge(); /* Send a fallingEdge to LCD to make it read the CMD */
}

void LCD_vSendData(uint8 Data)
{
	/* PUT Half Data On PORT */
	PORT(DataPort) &= 0x0F; /*clear where we Put data*/
	PORT(DataPort) |= (Data & 0xF0);	/* write our data */
	DIO_vWritePin(ControlPort,RS,DIO_HIGH);	/* Set RS as 1 to Define it as data */
	LCD_vSendFallingEdge(); /* Send a fallingEdge to LCD to make it read the CMD */
	
	/* PUT Other Half Data On PORT */
	PORT(DataPort) &= 0x0F;   /*clear where we Put data*/
	PORT(DataPort) |= (Data << 4); /* write our data */
	DIO_vWritePin(ControlPort,RS,DIO_HIGH);	/* Set RS as 1 to Define it as data */
	LCD_vSendFallingEdge(); /* Send a fallingEdge to LCD to make it read the CMD */
	
	AutoShiftScreen();
}


#endif