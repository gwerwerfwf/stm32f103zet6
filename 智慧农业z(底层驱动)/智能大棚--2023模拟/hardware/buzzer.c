#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Buzzer_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  
	//typedef struct {}GPIO_InitTypeDef;
	
	GPIO_InitTypeDef GPIO_InitStructure;//构建函数框架，使能GPIO始终
	
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	
  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
	
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOD,  &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
}

void Buzzer_on(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	
}

void Buzzer_off(void)
{
		GPIO_SetBits(GPIOD,GPIO_Pin_0);
}

void Buzzer_Lock_ON(void)
{
	Buzzer_on();
	Delay_ms(700);
	Buzzer_off();
}

