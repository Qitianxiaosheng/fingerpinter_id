#ifndef _BEEP_H
#define _BEEP_H

#include <stc15f2k60s2.h>

sbit SPEA = P1^6;

void turn_on_speaker(void);//有源蜂鸣器启动时J7的5,3用跳线帽连在一起
void turn_off_speaker(void);

void success_speaker(void);//成功时发出清脆的声音
void alarm_speaker(void); //失败时发出警报	
void no_speaker(void);

#endif