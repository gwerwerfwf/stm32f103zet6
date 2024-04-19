#include "stm32f10x.h"                  // Device header
#include "MyUSART.h"
#include "esp.h"
#include <string.h>
#include "Delay.h"

char Buf[1024];
uint8_t Flag1;
unsigned char i;

void MyUSART_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//1.开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;                 //初始化GIPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;              //初始化串口
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity =USART_Parity_No ;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init (USART1,&USART_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
}

void MyUSART_SendString(char* str)
{
	uint8_t stri=0;
	while(str[stri] != '\0')
		USART_SendData (USART1,str[stri++]);
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		Buf[i++]=USART_ReceiveData(USART1);
	    if(Buf[0]=='+'&&Buf[1]=='I'&&Buf[2]=='P'&&Buf[3]=='D')
		{
			if(Buf[i-1]==':')
			{
				i=0;
				memset(Buf,0,sizeof(Buf));
			}
		}
		if(Buf[0]=='C'&&Buf[1]=='L'&&Buf[2]=='O'&&Buf[3]=='S'&&Buf[4]=='E'&&Buf[5]=='D')
		{
		        i=0;
				memset(Buf,0,sizeof(Buf));
		}
		if(Buf[i-1]=='}')
		{
		      Comman_Rec();
	          memset(Buf,0,sizeof(Buf));
	          i=0;
		}
		else if(Buf[i-1]=='>')
		{
		  Flag1=7;
		  memset(Buf,0,sizeof(Buf));
		  i=0;
		}
		else if(Buf[i-1]=='\n'|Buf[i-2]=='\r')
		{
			Buf[i-2]='\0';
			if(strcmp(Buf,"STATUS:2")==0)
				Flag1=2;
			if(strcmp(Buf,"STATUS:3")==0)
				Flag1=3;
			if(strcmp(Buf,"STATUS:4")==0)
				Flag1=4;
			if(strcmp(Buf,"STATUS:5")==0)
				Flag1=5;
			i = 0;
		}
	}
}
