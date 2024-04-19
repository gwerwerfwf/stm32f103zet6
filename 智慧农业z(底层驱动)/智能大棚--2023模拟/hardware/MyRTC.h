#ifndef __MYRTC_H
#define __MYRTC_H

extern uint16_t MyRTC_Time[];
//extern long cnt;

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);

long GetTime(void);
#endif
