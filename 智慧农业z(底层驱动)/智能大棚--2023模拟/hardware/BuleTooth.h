#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H
#include "stdio.h"

void BuleTooth_Init(void);
void Explan(void);
uint8_t BlueTooth_Link_Station(void);
void Send_Equip_Data(void);
void USART2_SendString(char* str);
void USART2_printf (char *fmt, ...);


#endif

