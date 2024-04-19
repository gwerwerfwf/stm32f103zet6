#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f10x.h"

#define OW_DIR_OUT() 	mode_output1()
#define OW_DIR_IN() 	mode_input1()
#define OW_OUT_LOW() 	(GPIO_ResetBits(GPIOA,GPIO_Pin_11))
#define OW_GET_IN()  	(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11))

#define OW_SKIP_ROM 		0xCC
#define DS18B20_CONVERT 0x44
#define DS18B20_READ 		0xBE


void ds18b20_init_x(void);
float ds18b20_read(void);

#endif


