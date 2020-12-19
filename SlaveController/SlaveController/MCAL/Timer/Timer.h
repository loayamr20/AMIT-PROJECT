/*
* Timer.h
*
* Created: 11/27/2020 3:19:44 PM
*  Author: Loay
*/


#ifndef TIMER_H_
#define TIMER_H_

#include "FrameWork/Framework.h"

// TCNT0   Timer Counter
// TCCR0   Timer counter control Register
// TIFR    Timer Interrupt Flag Register


typedef enum
{
	Timer_Normal,Timer_CTC,Timer_PWM,Timer_FastPWM
}TimerModes;

typedef enum
{
	t_Stoped,
	t_clock,
	t_clock8th,
	t_clock64th,
	t_clock256th,
	t_clock1024th,
	t_clockFE,
	t_clockRE,
}TimerClocks;

typedef struct {
	volatile uint32	 TimerOverFlows;
	TimerModes Mode;
	TimerClocks ClockSource;
	volatile uint8 ocr;
	
}Timer;


Timer timer0;
void Timer0_v1msInit();
void Timer0_vInit(Timer * timer);
void Timer0_vStart();
void Timer0_vStop();
uint16 Timer_u16PassedSeconed(Timer * timer);
uint16 Timer_u16PassedMinutes(Timer * timer);
#endif /* TIMER_H_ */