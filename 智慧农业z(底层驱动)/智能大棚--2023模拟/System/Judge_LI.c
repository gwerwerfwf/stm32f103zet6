#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Motor.h"
#include "Delay.h"
#include "OLED.h"
extern uint8_t Switch,LdStation,DeviceId;
int tem=0;
 
void Judge2(uint16_t Li,uint8_t Flag)
{
	Motor_Init ();
	if(Switch==1)
	{
	    if(LdStation==1)
		   Motor_SetSpeed(40);
	    else
		   Motor_SetSpeed(0);
	}
	else//卷帘是否开启
	{	
	    if(Li<Flag&&tem == 0)
		{
			tem=1;
			Motor_SetSpeed(40);
			Delay_ms(10000);
			Motor_SetSpeed(0);
		}
		else
		{
			Motor_SetSpeed(0);               
		}
	}     
}
