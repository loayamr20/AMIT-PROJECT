/*
* Framework.h
*
* Created: 11/21/2020 5:27:16 PM
*  Author: Loay
*/


#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

/* Common used Includes */
#include "STD_TYPES.h"
#include "Config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
/* Common Used MACROS */
#define SET_BIT(REGISTER,BIT_NUM) (REGISTER = REGISTER | (1<<BIT_NUM))
#define CLR_BIT(REG,BIT_NUM)   (REG = REG &(~(1<<BIT_NUM)))
#define TOGGLE_BIT(REG,BIT_NUM)   (REG = REG ^ (1<<BIT_NUM))
#define GET_BIT(PortName,bit_number) ((PortName >> bit_number)& 0x01)
#define IS_BIT_SET(REG,BIT_NUM) ((REG &(1<<BIT_NUM))>>BIT_NUM)
#define IS_BIT_CLEARED(REG,BITNUM) (!((REG &(1<<BIT_NUM))>>BIT_NUM)
#define ROR(REG,BIT_NUM)  (REG = (REG>>BIT_NUM) | (REG<<(8-BIT_NUM)))
#define ROL(REG,BIT_NUM) (REG = (REG<<BIT_NUM) | (REG>> (8-BIT_NUM)))

/* reverse integer Digits */
static uint32 reversDigits(uint32 num)
{
	uint32 rev_num = 0;
	while (num > 0)
	{
		rev_num = rev_num*10 + num%10;
		num = num/10;
	}
	return rev_num;
}

/* get how many digits in integer */
static uint8 integer_get_length(sint32 x) {
	uint8 N = 1;
	/* get number absolute value */
	if (x < 0)
	{
		x *= -1;
	}
	while(x > 9)
	{
		N++;
		x /= 10;
	}
	return N;
}

/* convert string to integer */
static sint32 string_to_integer(uint8 * str) {
	sint32 i, n;
	sint8 multiplier = 1;
	/* check if string is in -ve */
	if (*str == '-')
	{
		multiplier = -1;
		str++;
	}
	n = 0;
	while(*str)
	{
		n = n * 10 + (*str) - '0';
		str++;
	}
	/*
	for (i = 0; a[i] != '\0'; i++) {
		n = n * 10 + a[i] - '0';
	}*/
	return (n * multiplier);
}

/* convert integer to string */
static void intger_to_string (uint8 * buffer, sint32 intgr)
{
	sint32 y = 1;
	uint8 index = 0;
	/* check if add -ve sign */
	if(intgr < 0)
	{
		buffer[index]='-';
		intgr *= -1;
		index++;
	}
	/* get value length */
	while(intgr > 0)
	{
		y = ((y*10) + (intgr%10));
		intgr /= 10;
	}
	/* add value to buffer */
	while(y > 1 )
	{
		buffer[index] = (uint8)((y%10)+48);
		y /= 10;
		index++;
	}
	buffer[index] = '\0';
}

/* Conversation Equation For LM35 module */
static uint8 ADC_to_Temp(uint16 ADC_val)
{
	return (uint8)(ADC_val/(2*2.048f));
}

#endif /* FRAMEWORK_H_ */