#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	/*初始化时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	/**************/
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OutputState= TIM_OutputState_Enable;//设置输出使能
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置输出比较的模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High ;//设置输出比较的极性
	TIM_OCInitStructure.TIM_Pulse=0;//设置CCR的值，与占空比相关
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	
}

void PWM_CompareSet1(uint16_t compare)
{
	TIM_SetCompare1(TIM3,compare);//用来单独更改CH1通道CCR的值
}

void PWM_SetCompare3(uint16_t compare3)
{
	TIM_SetCompare2(TIM3,compare3);
}

