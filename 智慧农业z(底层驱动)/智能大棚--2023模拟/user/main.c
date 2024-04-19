#include "stm32f10x.h"       
#include "Delay.h"
#include "Buzzer.h"
#include "OLED.H"
#include "ADC.h"
#include "DHT11.H"
#include "PWM.h"
#include "MyUSART.h"
#include "DS18B20.h"
#include "Judge_Temp.h"
#include "Judge_LI.h"
#include "Judge_Season.h"
#include "ESP.h"
#include "MyRTC.h"
#include "stdio.h"
#include "stdlib.h"
#include "RC522.h"
#include "BuleTooth.h"
#include "time.h"
#include "LED.h"
#include "human.h"
#include "Control_Light.h"
#include "SU-03T.h"
#define maxsize 512
extern  char buffer1[];
struct data
{
   float Temp;
   uint8_t temp;
   uint16_t li;
	int tem,tem1,tem2;
   long cnt;
};
struct data Trans_data[maxsize];

uint16_t AD1,li,AD2,DB;
uint8_t temp,humi,keynum,ccr=0,keynum1=0;
uint8_t spring=1,summer=2,autumn=3,winter=4;
uint8_t season,count=0,j,a=0;
uint8_t Flag2,Flag3,Flag4,Flag5;
float Temp;
int AP,m;
long cnt;
extern int tem,tem1,tem2;
extern _calendar_obj calendar;
int main(void)
{
	/*******初始化各个模块*****/
	 OLED_Init();
	 Buzzer_Init();
	 MyUSART_Init();
	 AD_Init();
	 DHT11_Init();
	 ds18b20_init_x();
	 PWM_Init();
     SU03T_Init();
     Light_Init();
	 ESP_WIFI_Init();
	 ESP_TCPServicer_Init();//连接TCP服务器
	 LED_Init ();
	 human_Init();
	 RTC_Init();	  
	 BuleTooth_Init();
	/***************************/
	 
	/******OLED显示*************/
	 OLED_ShowString(1,1,"LI:000Lux");
	 OLED_ShowString(2,1,"Tem1:00.00C");
	 OLED_ShowString(3,1,"Tem2:00.00C");
	/***************************/
	
//	uint8_t t=0;
		
	while(1)
	{
		//keynum=Key_GetNum();
		
		
			//keynum1++;
			if(keynum1==1)
			{
				ccr=5;
			}
			else if(keynum1==2)
			{
			  ccr=50;
			}
			else if(keynum1==3)
			{
			   ccr=100;
			}
			else if(keynum1==4)
			{
			  ccr=0;
			  keynum1=0;
			}
		
		OLED_ShowNum(3,14,keynum1,1);
	    OLED_ShowNum(1,15,AP,1);
        PWM_CompareSet1(ccr);
//			OLED_ShowNum(4,1,calendar.w_year,4);									  
//			OLED_ShowNum(4,6,calendar.w_month,2);									  
//			OLED_ShowNum(4,8,calendar.w_date,2);
			OLED_ShowNum(4,1,calendar.hour,2);									  
			OLED_ShowNum(4,4,calendar.min,2);	
//           calendar.sec=calendar.sec-1;	
			OLED_ShowNum(4,7,calendar.sec,2);
				
	      /**** ***光照强度显示*****/
		 AD1=AD_GetValue(ADC_Channel_1);
		 li=100-(AD1/4096.0*100);
		 OLED_ShowNum(1,4,li,2);
//		 Delay_ms(100);
		
		
		 AD2=AD_GetValue(ADC_Channel_2);
		 PWM_CompareSet1(ccr);
		 DB=100-(AD2/4096.0*100);
		 OLED_ShowNum(4,10,AD2,2);
	 /************************/
		
		/******温度,湿度显示*****/
		DHT11_Read_Data(&temp,&humi);
		     PWM_CompareSet1(ccr);
//		OLED_ShowNum(2,6,humi,2);
		OLED_ShowNum(2,6,temp,2);
		Temp=ds18b20_read();
		     PWM_CompareSet1(ccr);
		OLED_ShowNum(3,6,Temp,2);
		OLED_ShowNum(3,9,(int16_t)(Temp*100)%100,2);
	         PWM_CompareSet1(ccr);   
        human_enter();
		     PWM_CompareSet1(ccr);
		Send_Equip_Data();
//		OLED_ShowNum(4,1,cnt,10);
//		OLED_ShowNum(1,11,Flag3,2);
//		OLED_ShowNum(1,8,Flag2,2);
//		OLED_ShowNum(2,10,Flag4,2);
		     PWM_CompareSet1(ccr);
     	Judge1(temp,Temp,Flag2,Flag3);
		     PWM_CompareSet1(ccr);
		Judge2(li,40);
		 PWM_CompareSet1(ccr);
		 if(AP==2)//断网重连的情况，需要重新连接TCP服务器
		 {
			 PWM_CompareSet1(ccr);
			 //OLED_ShowNum(3,13,a,1);
		     for(int i=0;i<a;i++)
			 {
				 OLED_ShowString(4,1,"TCP Linking...");
				 ESP_TCPServicer_Init();//连接上后要把存的数据全部发过去
			     Transmit_Data2(Trans_data[i].li,Trans_data[i].temp,Trans_data[i].Temp,Trans_data[i].tem,Trans_data[i].tem1,Trans_data[i].tem2,Trans_data[i].cnt);
			 PWM_CompareSet1(ccr);
				 //Delay_ms (2000);
			 }
            free(Trans_data);
		    a=0;
		 }
		 else if(AP==3)//正常连接
		 {
			OLED_ShowString(4,1,"wifi connected");
		    Transmit_Data(li,temp,Temp,tem,tem1,tem2);
		 }
		 else if(AP==4)
		 {
			  ESP_TCPServicer_Init();
		      Transmit_Data(li,temp,Temp,tem,tem1,tem2);
		 }
		 else if(AP==5)//突然断开WIFI连接，数据存在线性表里
		 {
			 OLED_ShowString(4,1,"wifi disconnected");
			 Trans_data[a].temp=temp;
			 Trans_data[a].Temp=Temp;
		     Trans_data[a].li=li;
			 Trans_data[a].tem=tem;
			 Trans_data[a].tem1=tem1;
			 Trans_data[a].tem2=tem2;
			 a++;
		 }
		 if(Flag1==6)//传输时发生断开连接,数据存在线性表里
		 {  
			 Trans_data[a].temp=temp;
			 Trans_data[a].Temp=Temp;
		     Trans_data[a].li=li;
			 Trans_data[a].tem=tem;
			 Trans_data[a].tem1=tem1;
			 Trans_data[a].tem2=tem2;
			 a++;
	     }
		  AP=ESP_WIFI_Status();
		    PWM_CompareSet1(ccr);
    }
     
}

