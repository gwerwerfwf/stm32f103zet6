#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "stdio.h"
#include "Delay.h"
#include "OLED.h"
#include "stdlib.h"
#include <stdarg.h>
unsigned char n;
extern int AP;
extern uint8_t DeviceId;
#define CMD_BUFFER_LEN 1024
char buffer[CMD_BUFFER_LEN+1];

void BuleTooth_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
}

void Explan(void)
{
	 OLED_ShowString(3,13,buffer);
	 memset(buffer,0,sizeof(buffer));
}

void USART2_SendString(char* str)
{
	uint8_t stri=0;
	while(str[stri] != '\0')
		USART_SendData (USART2,str[stri++]);
}

uint8_t BlueTooth_Link_Station(void)//连接的时候输出高电平
{
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1)
	{
	   OLED_ShowString(4,13,"link");
		return 1;
	}
	else
	{
		 OLED_ShowString(4,13,"lose");
		 return 0;
	}
}

void USART2_printf (char *fmt, ...)
{
        // CMD_BUFFER_LEN长度自己定义吧
        uint16_t i = 0;
        va_list arg_ptr;
        va_start(arg_ptr, fmt);  
        vsnprintf(buffer, CMD_BUFFER_LEN+1, fmt, arg_ptr);
        while ((i < CMD_BUFFER_LEN) && strlen(buffer))
        {
                USART_SendData(USART2, (uint8_t) buffer[i++]);
                while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
        }
        va_end(arg_ptr);
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		buffer[n++]=USART_ReceiveData(USART2);
        if(buffer[n-1]=='@')
		{
          buffer[n-1]='\0';
		  n=0;
		  Explan();
		}
	}
}

void Send_Equip_Data(void)
{
	if(BlueTooth_Link_Station()==1)
	{
		USART2_printf("设备号:%d\r\nWIFI连接状态:%d",DeviceId,AP);
	}
}
