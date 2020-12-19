/*
* Timer.c
*
* Created: 11/27/2020 3:19:54 PM
*  Author: Loay
*/

#include "Timer.h"

void Timer0_v1msInit()
{
	//values to give 1ms tick
	timer0.ClockSource = t_clock64th;
	timer0.Mode = Timer_CTC;
	timer0.ocr = 125;
	Timer0_vInit(&timer0);
}
void Timer0_vInit(Timer * timer)
{
	/*choose Mode*/
	switch (timer->Mode)
	{
		case Timer_Normal:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case Timer_CTC:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case Timer_PWM:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case Timer_FastPWM:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		default:
		/* Your code here */
		break;
	}
	
	OCR0 = timer->ocr;
	
	/* Choose Prescaler */
	switch (timer->ClockSource)
	{
		case t_Stoped:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		case t_clock:
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		case t_clock8th:
		CLR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		case t_clock64th:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		case t_clock256th:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		case t_clock1024th:
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		case t_clockFE:
		CLR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		case t_clockRE:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		default:
		/* Your code here */
		break;
	}
}
void Timer0_vStart(){
	/*enable ocieo from timsk register*/
	SET_BIT(TIMSK,OCIE0);
}
void Timer0_vStop(){
	/*enable ocieo from timsk register*/
	CLR_BIT(TIMSK,OCIE0);
}

uint16 Timer_u16PassedSeconed(Timer * timer){
	return (uint16)(timer->TimerOverFlows / 1000);
}

uint16 Timer_u16PassedMinutes(Timer * timer){
	return (uint16) (Timer_u16PassedSeconed(timer)/60);
}
