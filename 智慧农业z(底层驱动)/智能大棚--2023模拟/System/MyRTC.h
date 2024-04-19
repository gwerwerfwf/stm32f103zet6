#ifndef __MYRTC_H
#define __MYRTC_H

typedef struct 
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;			
	uint16_t w_year;
	uint8_t  w_month;
	uint8_t  w_date;
	uint8_t  week;		 
}_calendar_obj;			 
extern _calendar_obj calendar;	

extern uint8_t const mon_table[12];	
void Disp_Time(uint8_t x,uint8_t y,uint8_t size);
void Disp_Week(uint8_t x,uint8_t y,uint8_t size,uint8_t lang);
uint8_t RTC_Init(void);        
uint8_t Is_Leap_Year(uint16_t year);
uint8_t RTC_Alarm_Set(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec);
uint8_t RTC_Get(void);            
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day);
uint8_t RTC_Set(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec);

#endif
