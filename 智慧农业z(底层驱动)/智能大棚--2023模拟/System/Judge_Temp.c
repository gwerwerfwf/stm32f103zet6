#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
extern uint8_t Switch,Motor1,Motor2,DeviceId;
int tem1=0,tem2=0;

void Judge1(uint8_t temp1,float temp2,uint8_t flag1,float flag2)
{
	LED_Init();
	if(Switch==1)//进入手动模式
	{
		if(Motor1==1)
		{
		  LED1_ON();
		}
		
		if(Motor2==1)
		{
		 LED2_ON();
		}
	}
	 else 
	{
	   if(temp1>flag1)//通风管理
	   {
		   tem1=1;
		  LED1_ON();
	   }
	   else
	   {
		   tem1=0;
	      LED1_OFF ();
	   }
	    if(temp2>flag2)//灌溉系统
	   {
		   tem2=1;
		 LED2_ON();
	   }
	   else 
	   {
		   tem2=0;
	      LED2_OFF();
	   }
   }	 
}

