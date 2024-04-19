#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "OLED.h"

extern uint16_t Rxdata;

void MyUSART_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;//选择为接收模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//选择校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//选择停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//选择数据接收长度
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}



void SendData(uint8_t Data)
{
	USART_SendData(USART1,Data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void SendArr(uint8_t *arr,uint16_t len)
{
	int i;
	for(i=0;i<len;i++)
	{
		SendData(arr[i]);
	}	
}

void SendString(char *string)
{
	int i=0;
	for(i=0;string[i]!='\0';i++)
	{
		SendData(string[i]);
	}
}

uint32_t Sendpow(uint32_t x,uint32_t y)
{
	int result=1;
  while(y)
	{
	  result*=x;
		y--;
	}
	return result;
}

void SendNum(uint32_t Num,uint8_t len)
{
	uint8_t i;
	//int temp;
	for(i=0;i<len;i++)
	{
		SendData(Num / Sendpow(10,len-i-1) % 10 + '0');	
	}
}

int fputc(int ch, FILE *f)
{
	SendData(ch);
	return ch;
}

void My_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	SendString(String);
}

