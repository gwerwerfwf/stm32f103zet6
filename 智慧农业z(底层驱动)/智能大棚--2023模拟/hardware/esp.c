#include "stm32f10x.h"                  // Device header
#include "MYUSART.h"
#include "Delay.h"
#include "stdio.h"
#include "string.h"
#include "cJSON.h"
#include "stdlib.h"
#include "OLED.h"
#include "string.h"
#include "time.h"
#include "MyRTC.h"

extern char Buf[1024];
extern time_t time_cnt1;
const char* WIFI="TP-LINK_443B5C";
const char* PASS="123456789";
const char* IP="192.168.1.101";
const char* COMNum="12444";
extern uint8_t Flag2,Flag3,Flag4,Flag1;
uint8_t Switch=0,Motor1,Motor2,LdStation,Status=1,DeviceId;
void ESP_TCPServicer_DeInit(void);
void ESP_PASS_SEND(void);
void ESP_PASS_ON(void);

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
//int fputc(int ch,FILE *f )//printf重定向 
{
	while(USART_GetFlagStatus (USART1,USART_FLAG_TC) == RESET);
	USART_SendData(USART1,(uint8_t)ch);
	return ch;
}

void Transmit_Data(uint8_t ld,uint8_t temp1,uint8_t temp2,uint8_t light,uint8_t vent,uint8_t irr)//以JSON格式发送数据到服务器
{
   memset(Buf,0,sizeof(Buf));
   printf("AT+CIPSEND=85\r\n");
   Delay_ms(500);
   if(Flag1==7)
   {
	   printf("{\"ld\":\"%d\",\"temp1\":\"%d\",\"temp2\":\"%d\",\"light\":\"%d\",\"vent\":\"%d\",\"irr\":\"%d\",\"deviceId\":\"1\"}",ld,temp1,temp2,light,vent,irr);
	   Delay_ms(500);
	   memset(Buf,0,sizeof(Buf));
   }
}

void Transmit_Data2(uint8_t Li,uint8_t temp1,uint8_t temp2,uint8_t vent,uint8_t light,uint8_t irr,long Cnt)//以JSON格式发送数据到服务器
{
	//OLED_ShowNum(4,1,Cnt,10);
   memset(Buf,0,sizeof(Buf));
   printf("AT+CIPSEND=105\r\n");
   Delay_ms(1000);
	
   if(Flag1==7)
   {
	   printf("{\"temp1\":\"%d\",\"temp2\":\"%d\",\"ld\":\"%d\",\"light\":\"%d\",\"vent\":\"%d\",\"irr\":\"%d\",\"deviceId\":\"1\",\"time\":\"%ld\"}",temp1,temp2,Li,light,vent,irr,Cnt);
	   Delay_ms(1000);
	   memset(Buf,0,sizeof(Buf));
   }
}

void ESP_WIFI_Init(void)
{
	 memset(Buf,0,sizeof(Buf));
	 printf("AT+CWMODE=1\r\n");
	 Delay_ms(2000);

	 memset(Buf,0,sizeof(Buf));
	 printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,PASS);
	 Delay_ms(4000);
	 while(strcmp(Buf,"OK")==0)
	 {
	   memset(Buf,0,sizeof(Buf));
     }
}
//需要解决总是busy的问题
uint8_t ESP_TCPServicer_Init(void)
{
    
	memset(Buf,0,sizeof(Buf));
	printf("AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",IP,COMNum);
	Delay_ms(1000);
	if(strcmp(Buf,"OK")==0)
	{
	    return 4;
	}
    /*
	memset(Buf,0,sizeof(Buf));//打开透传模式
	printf("AT+CIPMODE=1\r\n");
	Delay_ms(2000);
	if(strcmp(Buf,"OK")!=0)
      return 2;
	
	memset(Buf,0,sizeof(Buf));
	printf("AT+CIPSEND\r\n");
	Delay_ms(2000);
	if(Buf[0]=='>'&&Buf[1]=='\0')
	{
	  memset(Buf,0,sizeof(Buf));
	  return 3;
	}*/
	
	
}

void ESP_PASS_ON(void)
{
    memset(Buf,0,sizeof(Buf));//打开透传模式
	printf("AT+CIPMODE=1\r\n");
	Delay_ms(2000);
	if(strcmp(Buf,"OK")!=0)
      memset(Buf,0,sizeof(Buf));
}

void ESP_PASS_SEND(void)
{
	memset(Buf,0,sizeof(Buf));
	printf("AT+CIPSEND\r\n");
	Delay_ms(2000);
	memset(Buf,0,sizeof(Buf));
}


uint8_t ESP_WIFI_Status(void)
{
	memset(Buf,0,sizeof(Buf));
    printf("AT+CIPSTATUS\r\n");
	Delay_ms(500);
	return Flag1;
}

void ESP_TCPServicer_DeInit(void)
{
		memset(Buf,0,sizeof(Buf));
		printf("+++");

	    Delay_ms(1000);
		memset(Buf,0,sizeof(Buf));
	    
		printf("AT+CIPMODE=0\r\n");
		Delay_ms(1000);
	    memset(Buf,0,sizeof(Buf));
	    
	    printf("AT+CIPMODE=0\r\n");
		Delay_ms(1000);
	    memset(Buf,0,sizeof(Buf));			
}

void Comman_Rec(void)//解析服务器发送过来的JSON格式数据
{
	  size_t json_length = strlen(Buf);
      cJSON *root=cJSON_ParseWithLength(Buf,json_length);
    
      cJSON *ld = cJSON_GetObjectItem(root, "ld");
	  Flag4= ld->valueint;//光照阈值
	
      cJSON *swi = cJSON_GetObjectItem(root, "swi");
      Switch= swi->valueint;//手动或者自动模式
      OLED_ShowNum(3,13,Switch,1);
		
      cJSON *motor1 = cJSON_GetObjectItem(root, "light1");
      Motor1= motor1->valueint;//
    
      cJSON *deviceId = cJSON_GetObjectItem(root, "deviceId"); 
      DeviceId=deviceId->valueint;//风扇2的状态
    
      cJSON *temp1 = cJSON_GetObjectItem(root, "temp3");
	  Flag2= temp1->valueint;//温度1阈值
	
      cJSON *motor2 = cJSON_GetObjectItem(root, "irr1");
      Motor2= motor2->valueint;//灌溉
	  
	
      cJSON *temp2 = cJSON_GetObjectItem(root, "temp4");
	  Flag3=temp2->valueint;//温度2阈值
	
      cJSON *ldStatus = cJSON_GetObjectItem(root, "vent1");
	  LdStation= ldStatus->valueint;//光照状态
	  
      cJSON_Delete(root);
}

