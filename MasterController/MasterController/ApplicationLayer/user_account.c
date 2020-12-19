/*
* user_account.c
*
* Created: 12/17/2020 3:37:00 PM
*  Author: Loay
*/
#include "user_account.h"
//addresses
#define FIRST_RUN_ADDRESS 0x00
#define USER_NAME_ADRESS 0x08
#define PIN_CODE_ADDRESS 0x18
#define LOGIN_BLOCK_FLAG_ADRESS 0x24
#define PASSED_MINUTS_ADRESS 0x25
#define WRONG_COUNTER_ADRESS 0x26
//constants
#define FIRST_RUN_VALUE 0xFF

void user_vInt(User * user)
{
	uint8 F_Run = FIRST_RUN_VALUE;
	F_Run = EEPROM_u8Read(FIRST_RUN_ADDRESS);
	if (F_Run == FIRST_RUN_VALUE)
	{
		user->new_user = TRUE;
		EEPROM_vWrite(LOGIN_BLOCK_FLAG_ADRESS,0);
		user->login_blocked = FALSE;
		EEPROM_vWrite(WRONG_COUNTER_ADRESS,0);
		user->wrong_aremptes_counter = 0;
		EEPROM_vWrite(PASSED_MINUTS_ADRESS,0);
		user->Passed_block_minuts = 0;
	}else{
		user->new_user = FALSE;
		EEPROM_ReadSTR(USER_NAME_ADRESS,user->UserName,USER_NAME_LENGTH);
		EEPROM_ReadSTR(PIN_CODE_ADDRESS,user->PIN_CODE,PINCODE_LENGTH);
		uint8 block = EEPROM_u8Read(LOGIN_BLOCK_FLAG_ADRESS);
		if (block != 0)
		{
			user->login_blocked = TRUE;
		}
		user->wrong_aremptes_counter = EEPROM_u8Read(WRONG_COUNTER_ADRESS);
		user->Passed_block_minuts = EEPROM_u8Read(PASSED_MINUTS_ADRESS);
		
	}
}

void setup_user(User * user)
{
	LCD_vPrint("First RUN !",clearScreen);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vPrint("you need to",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("set your PIN !",Apend);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vPrint("set user Name:",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_CursorState(Cursor_Blinking);
	Uart_GetString(user->UserName,USER_NAME_LENGTH,FALSE,FALSE);
	LCD_CursorState(Cursor_OFF);
	LCD_vPrint("Good !",clearScreen);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("Now Set PINCODE !",clearScreen);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vPrint("set PINCODE:",clearScreen);
	LCD_vMoveCursor(1,0);
	LCD_CursorState(Cursor_Blinking);
	Uart_GetString(user->PIN_CODE,PINCODE_LENGTH,TRUE,TRUE);
	LCD_CursorState(Cursor_OFF);
	LCD_vPrint("Good !",clearScreen);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("Account Saved !",clearScreen);
	_delay_ms(SHOW_STRING_DELAY);
	EEPROM_vWrite(FIRST_RUN_ADDRESS,1);
	EEPROM_WriteSTR(USER_NAME_ADRESS,user->UserName,USER_NAME_LENGTH);
	EEPROM_WriteSTR(PIN_CODE_ADDRESS,user->PIN_CODE,PINCODE_LENGTH);
	EEPROM_vWrite(LOGIN_BLOCK_FLAG_ADRESS,0);
	EEPROM_vWrite(WRONG_COUNTER_ADRESS,0);
	EEPROM_vWrite(PASSED_MINUTS_ADRESS,0);
}

void Check_Wrong_atempt(boolean val)
{
	if (val)
	{		
		current_user.wrong_aremptes_counter +=1;
		EEPROM_vWrite(WRONG_COUNTER_ADRESS,current_user.wrong_aremptes_counter);
	}
	if (current_user.wrong_aremptes_counter == MAX_WRONG_ATEMPT)
	{
		current_user.login_blocked = TRUE;
		EEPROM_vWrite(LOGIN_BLOCK_FLAG_ADRESS,1);
	}	
	if (current_user.login_blocked)
	{
		LED_vTurnOn(&BlockLED)	;
		Timer0_vStart();
		timer0.TimerOverFlows = current_user.Passed_block_minuts * 1000 * 60;
		uint16 passed_time = 0;
		uint16 old_t_val = 100000;
		uint16 block_time = LOGIN_BLOCK_WAIT - current_user.Passed_block_minuts;
		while (block_time > 0)
		{
			passed_time = Timer_u16PassedMinutes(&timer0);
			if (old_t_val != passed_time)
			{
				/* 1 mint passed */
				old_t_val = passed_time;
				current_user.Passed_block_minuts = old_t_val;	
				EEPROM_vWrite(PASSED_MINUTS_ADRESS,current_user.Passed_block_minuts);
				block_time = LOGIN_BLOCK_WAIT - current_user.Passed_block_minuts;	
				LCD_vPrint("Login blocked For",clearScreen);
				LCD_vMoveCursor(1,0);
				uint8 * Wait_Time_str[3];
				Num_To_Str(Wait_Time_str,block_time);
				LCD_vPrint(Wait_Time_str,Apend);
				LCD_vPrint(" Mints !",Apend);
			}
		}
		Timer0_vStop();
		timer0.TimerOverFlows = 0;		
		current_user.login_blocked = FALSE;
		current_user.wrong_aremptes_counter = 0;
		current_user.Passed_block_minuts = 0;
		EEPROM_vWrite(LOGIN_BLOCK_FLAG_ADRESS,0);
		EEPROM_vWrite(WRONG_COUNTER_ADRESS,0);
		EEPROM_vWrite(PASSED_MINUTS_ADRESS,0);	
		LED_vTurnOFF(&BlockLED)	;
	}
	
}

void user_vLogin()
{
	user_vInt(&current_user);
	if (current_user.new_user){
		setup_user(&current_user);
		user_vInt(&current_user);
	}
	Check_Wrong_atempt(FALSE);
	
uint8 Temp_UserName[USER_NAME_LENGTH+1] = {0}; // the extra is for null terminated pointer
while (1)
{
	LCD_vPrint("Enter User Name:",clearScreen);
	LCD_vMoveCursor(1,0);
	Uart_GetString(Temp_UserName,USER_NAME_LENGTH,FALSE,FALSE);
	if (str_comp(Temp_UserName,current_user.UserName,FALSE))
	{
		break;
	}	
	LCD_vPrint("Wrong user name !",clearScreen);
	_delay_ms(SHOW_STRING_DELAY);
	LCD_vMoveCursor(1,0);
	LCD_vPrint("Try again !",Apend);
	uint8 * wrong_times[2];
	Num_To_Str(wrong_times,(uint16) (MAX_WRONG_ATEMPT - current_user.wrong_aremptes_counter));
	LCD_vPrint(wrong_times,Apend);
	LCD_vPrint("try",Apend);
	_delay_ms(SHOW_STRING_DELAY);
	Check_Wrong_atempt(TRUE);
}

	uint8 temp_pincode[PINCODE_LENGTH+1]=  {0};  // the extra is for null terminated pointer
	while (1)
	{
		LCD_vPrint("Enter PINCODE:",clearScreen);
		LCD_vMoveCursor(1,0);
		Uart_GetString(temp_pincode,PINCODE_LENGTH,TRUE,FALSE);
		if (str_comp(temp_pincode,current_user.PIN_CODE,TRUE))
		{
			break;
		}
		LCD_vPrint("Wrong PINCODE !",clearScreen);
		_delay_ms(SHOW_STRING_DELAY);
		LCD_vMoveCursor(1,0);
		LCD_vPrint("Try again! ",Apend);
		uint8 * wrong_times[2];
		Num_To_Str(wrong_times,(uint16) (MAX_WRONG_ATEMPT - current_user.wrong_aremptes_counter));
		LCD_vPrint(wrong_times,Apend);
		LCD_vPrint("try",Apend);
		_delay_ms(SHOW_STRING_DELAY);
		Check_Wrong_atempt(TRUE);
	}
	
	
}
