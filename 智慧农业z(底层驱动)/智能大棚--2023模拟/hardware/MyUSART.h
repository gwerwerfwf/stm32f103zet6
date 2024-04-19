#ifndef __SERIAL_H__
#define __SERIAL_H__
#include <stdio.h>
#include <stdarg.h>
//void Serial_Init(void);
//void Serial_SendByte(uint8_t byte);
//void Serial_SendArray(uint8_t *Array,uint16_t Length);
//void Serial_SendString(char *String);
//void Serial_SendNum(uint32_t Num,uint8_t Length);
void MyUSART_Init(void);
void MyUSART_SendString(char* str);
extern char Buf[];
extern uint8_t Flag1;

#endif
