#ifndef _ESP__H__
#define _ESP__H__


void ESP_WIFI_Init(void);
uint8_t ESP_Pub(void);
void Comman_Rec(void);
uint8_t ESP_TCPServicer_Init(void);
void ESP_TCPServicer_DeInit(void);
void Transmit_Data(uint8_t ld,uint8_t temp1,uint8_t temp2,uint8_t light,uint8_t vent,uint8_t irr);
void Transmit_Data2(uint8_t Li,uint8_t temp1,uint8_t temp2,uint8_t vent,uint8_t light,uint8_t irr,long Cnt);
uint8_t ESP_WIFI_Status(void);
void ESP_PASS_ON(void);
void ESP_PASS_SEND(void);

#endif

