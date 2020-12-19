/*
* user_account.h
*
* Created: 12/17/2020 3:37:12 PM
*  Author: Loay
*/


#ifndef USER_ACCOUNT_H_
#define USER_ACCOUNT_H_
#include "FrameWork/Framework.h"
#include "Shared_Methods.h"
#include "MCAL/EEPROM/EEPROM.h"
#include "HAL/LED/LED.h"
#include "MCAL/Timer/Timer.h"

LED BlockLED;
//Settings
#define USER_NAME_LENGTH 15 
#define PINCODE_LENGTH 4  

typedef struct{
	uint8 UserName[USER_NAME_LENGTH +1]; // the extra is for null terminated pointer
	uint8 PIN_CODE[PINCODE_LENGTH+1]; // the extra is for null terminated pointer
	uint16 Passed_block_minuts;
	boolean new_user;
	boolean login_blocked;
	uint8 wrong_aremptes_counter;
	}User;

User current_user;

void user_vLogin();

#endif /* USER_ACCOUNT_H_ */