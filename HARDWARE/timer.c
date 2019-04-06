#include "timer.h"

u8 time_flag=0;
void time_ms_init(u8 t,u8 on_off)	  //��ʱ��0��ʼ����tΪ��ʱ�ĺ����� 
{
	TMOD=0X00;	 //��ʱ��0 ��ʽ0
	TH0=(65536-t*10000)/256;
	TL0=(65536-t*10000)%256; 
  TR0=on_off;
	EA=1;
	ET0=1;
}

void time0() interrupt 1
{
	time_flag++;
}