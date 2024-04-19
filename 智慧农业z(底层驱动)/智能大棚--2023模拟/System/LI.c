#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "ADC.h"

uint16_t AD1,li;


void LI_Value(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"LI:00%");


		AD1=GetValue();
		li=100-(AD1/4096.0*100);
		OLED_ShowNum(1,4,li,2);
		//OLED_ShowNum(2,1,AD1,2);
		Delay_ms(1000);

	 
}
