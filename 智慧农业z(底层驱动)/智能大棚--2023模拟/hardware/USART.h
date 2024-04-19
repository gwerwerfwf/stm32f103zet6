#ifndef __USART_H
#define __USART_h

void MyUSART_Init(void);
void SendDate(uint8_t Data);
void SendArr(uint8_t*arr,uint16_t len);
void SendString(char *string);
uint16_t Sendpow(uint16_t x,uint16_t y);
void SendNum(uint16_t num,uint16_t len);
void My_Printf(char *format, ...);
	

#endif
