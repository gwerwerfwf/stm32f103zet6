#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

//uint16_t MyRTC_Time[] = {2023, 8, 19, 16, 15, 00};
//天文划分四季法就是以春分（3月21日）、夏至（6月21日）、秋分（9月21日）、冬至（12月21日）作为四季的开始

struct date
{
	int month;
	int day;
};

uint8_t Judge3(void)
{
	 uint8_t season;
	 MyRTC_Init();
	 struct date judge_date;
	 MyRTC_ReadTime();
		
		OLED_ShowNum(4, 6, MyRTC_Time[0], 4);//年
		OLED_ShowNum(4, 11, MyRTC_Time[1], 2);//月
		OLED_ShowNum(4, 14, MyRTC_Time[2], 2);//日
		
		OLED_ShowNum(4, 6, MyRTC_Time[3], 2);//时
		OLED_ShowNum(4, 9, MyRTC_Time[4], 2);//分
		OLED_ShowNum(4, 12, MyRTC_Time[5], 2);//秒
	
//	  judge_date.month=MyRTC_Time[1];
//	  judge_date.day=MyRTC_Time[2];

//	  if((judge_date.month>3&&judge_date.month<6)||(judge_date.month==3&&judge_date.day>=21)||(judge_date.month==6&&judge_date.day<21))
//	      season=1;
//	  if((judge_date.month>6&&judge_date.month<9)||(judge_date.month==6&&judge_date.day>=21)||(judge_date.month==9&&judge_date.day<21))
//	      season=2;
//	  if((judge_date.month>9&&judge_date.month<12)||(judge_date.month==9&&judge_date.day>=21)||(judge_date.month==12&&judge_date.day<21))
//          season=3;
//	  if((judge_date.month>=1&&judge_date.month<3)||(judge_date.month==3&&judge_date.day<21)||(judge_date.month==12&&judge_date.day>=21))
//		  season=4;
		return season;
}

