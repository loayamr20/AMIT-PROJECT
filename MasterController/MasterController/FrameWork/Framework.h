/*
* Framework.h
*
* Created: 11/21/2020 5:27:16 PM
*  Author: Loay
*/


#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#include "STD_TYPES.h"
#include "Config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#define SET_BIT(REGISTER,BIT_NUM) (REGISTER = REGISTER | (1<<BIT_NUM))
#define CLR_BIT(REG,BIT_NUM)   (REG = REG &(~(1<<BIT_NUM)))
#define TOGGLE_BIT(REG,BIT_NUM)   (REG = REG ^ (1<<BIT_NUM))
#define GET_BIT(PortName,bit_number) ((PortName >> bit_number)& 0x01)
#define IS_BIT_SET(REG,BIT_NUM) ((REG &(1<<BIT_NUM))>>BIT_NUM)
#define IS_BIT_CLEARED(REG,BITNUM) (!((REG &(1<<BIT_NUM))>>BIT_NUM)
#define ROR(REG,BIT_NUM)  (REG = (REG>>BIT_NUM) | (REG<<(8-BIT_NUM)))
#define ROL(REG,BIT_NUM) (REG = (REG<<BIT_NUM) | (REG>> (8-BIT_NUM)))
#define IS_ASCII_PRINTABLE(charchter) (charchter >= 32 && charchter <= 126)
#define IS_ALPHA_CHAR(charchter) ((charchter >= 'a' && charchter <= 'z') || (charchter >= 'A' && charchter <= 'Z'))
#define IS_NUMRIC_CHAR(charchter) (charchter >= '0' && charchter <= '9')
#define IS_SYMBOL_CHAR(charchter)  ((charchter >= 32 && charchter <= 126) && !(((charchter >= 'a' && charchter <= 'z') || (charchter >= 'A' && charchter <= 'Z'))) && !((charchter >= '0' && charchter <= '9')))

static uint16 reversDigits(uint16 num)
{
	uint16 rev_num = 0;
	while (num > 0)
	{
		rev_num = rev_num*10 + num%10;
		num = num/10;
	}
	return rev_num;
}

static uint8 Get_Num_Length(uint16 x) {
	uint8 N = 1;
	while(x > 9)
	{
		N++;
		x /= 10;
	}
	return N;
}

static uint16 STR_to_Int(uint8 a[]) {
	uint16 i, n;
	n = 0;
	for (i = 0; a[i] != '\0'; i++) {
		n = n * 10 + a[i] - '0';
	}
	return n;
}

static void Num_To_Str (uint8 * str, uint16 val)
{
	uint8 i = 1;
	uint8 len = 0;
	if (val < 0)
	{
		len = Get_Num_Length(-val);
	}else{
		len = Get_Num_Length(val);
	}

	for(; i<=len; i++)
	{
		str[len-i] = (uint8) ((val % 10UL) + '0');
		val/=10;
	}
	str[i-1] = '\0';
}

static uint8 ADC_to_Temp(uint16 ADC_val)
{
	return (uint8)(ADC_val/(2*2.048f));
}

static size_t str_Length(uint8 * str){
	size_t L = 0;
	while(*str)
	{
		L++;
		str++;		
	}
	return L;
}

static boolean str_comp(uint8 * str1,uint8 * str2,boolean CaseSenstive)
{
	size_t L1 = str_Length(str1);
	size_t L2 = str_Length(str2);	
	if (L1 != L2)
	{
		return FALSE;
	}
	while (*str1)
	{
		if (*str1 != *str2)
		{
			//values are not equal
			if (CaseSenstive)
			{
				//we don't tolerate case sensitivity - >  return 0 (FALSE)
				return FALSE;
			}else{
				// if the are equal but with another case sensitivity  A = a but    a is shifted by 32 in ASCII
				//First Check if value is Alphabetical
				
				if (IS_ALPHA_CHAR(*str1) && IS_ALPHA_CHAR(*str2))
				{
						
					//if the shift between str1 and str2 is  32 +ve or -ve so the are equal but diff Case sensitivity
					sint8 v = (*str1 - *str2);
					if (!(v == 32 || v == -32))
					{
						return FALSE;
					}
				}else{
					return FALSE;  // they are not alphabetical so return FALSE
				}
			}
		}
		str1++;
		str2++;
	}
	// Values are Equal
	return TRUE;
}

#endif /* FRAMEWORK_H_ */