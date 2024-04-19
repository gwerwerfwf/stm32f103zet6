#include "stm32f10x.h"                  // Device header
#include "stdlib.h"
#include <stdarg.h>
#include "string.h"
#include "stdio.h"
#include "OLED.h"
#define CMD_BUFFER_LEN1 1024
 char buffer1[CMD_BUFFER_LEN1+1];
unsigned char q=0;

void SU03T_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//1.开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;                 //初始化GIPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;              //初始化串口
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity =USART_Parity_No ;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init (USART3,&USART_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
 }

void USART3_printf (char *fmt, ...)
{
        // CMD_BUFFER_LEN长度自己定义吧
        uint16_t i = 0;
        va_list arg_ptr;
        va_start(arg_ptr, fmt);  
        vsnprintf(buffer1, CMD_BUFFER_LEN1+1, fmt, arg_ptr);
        while ((i < CMD_BUFFER_LEN1) && strlen(buffer1))
        {
                USART_SendData(USART3, (uint8_t) buffer1[i++]);
              while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); 
        }
        va_end(arg_ptr);
		
}

void USART3_IRQnHandler(void)
{
   if(USART_GetITStatus(USART3,USART_IT_RXNE))
	{
		buffer1[q++]=USART_ReceiveData(USART3);
		OLED_ShowHexNum(1,11,buffer1[q],2);
	}
	USART_ClearITPendingBit(USART3 ,USART_IT_RXNE);
}


