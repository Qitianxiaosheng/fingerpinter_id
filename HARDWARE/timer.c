#include "timer.h"

unsigned int clk0=0;
void  TimerInit(void)
{
	ET0=1;     //��ʱ��0���ж�
	TL0=0x97;  //17ms�ĳ�ֵ
	TH0=0xBD;
  TR0=1;// ����ʱ��0	
	
}
void  Timer0(void) interrupt 1//��ʱ��0�жϺ���
{
 	TL0=0x97;
	TH0=0xBD;
	clk0++;   //��ʱ17ms
}


