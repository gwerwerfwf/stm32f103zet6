#include "stm32f10x.h"                  // Device header
#include "Buzzer.h"
#include "Delay.h"
#include "OLED.H"
#include "SU-03T.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <stdarg.h>

void human_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

void human_enter(void)
{
	//OLED_ShowNum(4,13,GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2),1);
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 1)
	{
		Delay_ms (500);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 1)
		{
			Buzzer_Lock_ON();
			USART3_printf("%d %d %d %d %d %d",0xAA,0x55,0x01,0x01,0x55,0xAA);
		}
	}
}
