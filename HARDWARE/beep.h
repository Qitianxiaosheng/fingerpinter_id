#ifndef _BEEP_H
#define _BEEP_H

#include <stc15f2k60s2.h>

sbit SPEA = P1^6;

void turn_on_speaker(void);//��Դ����������ʱJ7��5,3������ñ����һ��
void turn_off_speaker(void);

void success_speaker(void);//�ɹ�ʱ������������
void alarm_speaker(void); //ʧ��ʱ��������	
void no_speaker(void);

#endif