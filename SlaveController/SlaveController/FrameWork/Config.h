/*
 * Config.h
 *
 * Created: 11/21/2020 5:55:33 PM
 *  Author: Loay
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


/* set this to 1 if using the AMIT kit  */
#define KIT_MODE			0
/* Code flow configuration */
#define SHOW_STRING_DELAY   500
#define DEBUG_MODE			0
/* user_account.h configuration */
#define KIT_MODE			0
#define MAX_WRONG_ATEMPT	3
#define LOGIN_BLOCK_WAIT	1



#if KIT_MODE

#define F_CPU 16000000ul
#define LCD_4_BIT

#else

#define F_CPU 8000000ul

#endif

#endif /* CONFIG_H_ */