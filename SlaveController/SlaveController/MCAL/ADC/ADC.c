/*
* ADC.c
*
* Created: 12/06/2020 12:02:56 AM
*  Author: Loay
*/

#include "ADC.h"

void ADC_vInit(ADC_PreScalers preScaler,ADC_Vref vref)
{
	
	/* the are all from Data Sheet */
	
	/* adjust pre scaler */
	switch (preScaler)
	{
		case ADC_Scale_2:
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
		break;
		case ADC_Scale_4:
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
		break;
		case ADC_Scale_8:
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
		break;
		case ADC_Scale_16:
		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		case ADC_Scale_32:
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		case ADC_Scale_64:
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		case ADC_Scale_128:
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break;
		default:
		
		break;
	}
	
	/* adjust vref */
	switch (vref)
	{
		case verf_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case verf_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case verf_Internal:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
		default:
		/* Your code here */
		break;
	}
	
	/* Enable ADC */
	SET_BIT(ADCSRA,ADEN);
}

uint16 ADC_u16Read(uint8 Channel)
{
	/*Check Channel From Tabel 84 datasheet */
	ADMUX |= Channel;
	
	/* stat conversion */
	SET_BIT(ADCSRA,ADSC);
	
	/* Check Flag Finished */
	while(!GET_BIT(ADCSRA,ADIF))
	{
		/* wait */
	}
	
	/* Read ADC value */
	uint16 val = 0;
	val = (uint16)ADCL;
	val |= (uint16) (ADCH << 8);
	
	return val;
}