/*
 * ADC.h
 *
 * Created: 12/06/2020 12:03:04 AM
 *  Author: Loay
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "FrameWork/Framework.h"

#define ADC_Channel0 0
#define ADC_Channel1 1
#define ADC_Channel2 2
#define ADC_Channel3 3
#define ADC_Channel4 4
#define ADC_Channel5 5
#define ADC_Channel6 6
#define ADC_Channel7 7

typedef enum{
	ADC_Scale_2,
	ADC_Scale_4,
	ADC_Scale_8,
	ADC_Scale_16,
	ADC_Scale_32,
	ADC_Scale_64,
	ADC_Scale_128,
	}ADC_PreScalers;

typedef enum{
	verf_AREF,
	verf_AVCC,
	verf_Internal
	}ADC_Vref;

void ADC_vInit(ADC_PreScalers preScaler,ADC_Vref vref);
uint16 ADC_u16Read(uint8 Channel);






#endif /* ADC_H_ */