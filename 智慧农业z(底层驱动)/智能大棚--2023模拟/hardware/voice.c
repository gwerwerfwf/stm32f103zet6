#include "stm32f10x.h"                  // Device header
#include "Buzzer.h"
#include "OLED.h"

void voice_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void voice_warning(void)
{
   if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 1)
   {
	   OLED_ShowNum(4,1,1,1);
        //Buzzer_Lock_ON();
   }
}