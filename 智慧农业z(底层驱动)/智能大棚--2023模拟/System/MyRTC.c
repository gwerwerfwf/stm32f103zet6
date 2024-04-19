#include "sys.h"
#include "delay.h"
#include "myrtc.h" 

_calendar_obj calendar;
 
static void RTC_NVIC_Config(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
    NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);
}

uint8_t RTC_Init(void)
{
	
	uint8_t temp=0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	
	PWR_BackupAccessCmd(ENABLE);	
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != SET);
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x5050)		
	{	 			
		BKP_DeInit();	
		RCC_LSEConfig(RCC_LSE_ON);	
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&temp<250)
			{
			temp++;
			Delay_ms(10);
			}
		if(temp>=250)	
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
		else
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);	 
		RTC_WaitForLastTask();	
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);		
		RTC_WaitForLastTask();	
		RTC_EnterConfigMode();
		RTC_SetPrescaler(32767); 
		RTC_WaitForLastTask();	
		RTC_Set(2023,10,9,21,59,55);  
		RTC_ExitConfigMode();
		BKP_WriteBackupRegister(BKP_DR1,0X5050);
	}
	else
	{

		RTC_WaitForSynchro();	
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	
		RTC_WaitForLastTask();	
	}
	RTC_NVIC_Config();	    				     
	RTC_Get();
	return 0; 
}		 				    

void RTC_IRQHandler(void)//中断服务函数，每秒触发一次
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{							
		RTC_Get();
 	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);	
	    RTC_Get();						
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		
	RTC_WaitForLastTask(); 	    						 	   	 
}

uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) 
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	 			   
										 
uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 	  

const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
uint8_t RTC_Set(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec)//时间设置函数，以1970年1月1日为基准，1970~2099为合法年份
{
	uint16_t t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	
	{
		if(Is_Leap_Year(t))seccount+=31622400;
		else seccount+=31536000;			  
	}
	smon-=1;
	for(t=0;t<smon;t++)	   
	{
		seccount+=(u32)mon_table[t]*86400;
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;	   
	}
	seccount+=(u32)(sday-1)*86400; 
	seccount+=(u32)hour*3600;
    seccount+=(u32)min*60;	 
	seccount+=sec;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	  
	PWR_BackupAccessCmd(ENABLE);	 
	RTC_SetCounter(seccount);	

	RTC_WaitForLastTask();	  	
	return 0;	    
}


uint8_t RTC_Alarm_Set(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec)
{
	uint16_t t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	
	{
		if(Is_Leap_Year(t))seccount+=31622400;
		else seccount+=31536000;			  
	}
	smon-=1;
	for(t=0;t<smon;t++)	   
	{
		seccount+=(u32)mon_table[t]*86400;
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;	   
	}
	seccount+=(u32)(sday-1)*86400; 
	seccount+=(u32)hour*3600;
    seccount+=(u32)min*60;	 
	seccount+=sec; 			    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	   
	PWR_BackupAccessCmd(ENABLE);	  
	
	
	RTC_SetAlarm(seccount);
 
	RTC_WaitForLastTask();
	
	return 0;	    
}



uint8_t RTC_Get(void)//该函数用于获取时间和日期等数据
{
	static uint16_t daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	uint16_t temp1=0;	  
    timecount=RTC_GetCounter();	 
 	temp=timecount/86400;  
	if(daycnt!=temp)
	{	  
		daycnt=temp;
		temp1=1970;	
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))
			{
				if(temp>=366)temp-=366;
				else {temp1++;break;}  
			}
			else temp-=365;
			temp1++;  
		}   
		calendar.w_year=temp1;
		temp1=0;
		while(temp>=28)
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)
			{
				if(temp>=29)temp-=29;
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];
				else break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	
		calendar.w_date=temp+1;  	 
	}
	temp=timecount%86400;     			   
	calendar.hour=temp/3600;     	
	calendar.min=(temp%3600)/60; 		
	calendar.sec=(temp%3600)%60; 	
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);
	return 0;
}	 

															 
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day)
{	
	uint16_t temp2;
	uint8_t yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	if (yearH>19)yearL+=100;

	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			  
