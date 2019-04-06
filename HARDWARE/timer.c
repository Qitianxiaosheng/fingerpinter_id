#include "timer.h"

u8 time_flag=0;
void time_ms_init(u8 t,u8 on_off)	  //定时器0初始唬t为定时的毫秒数 
{
	TMOD=0X00;	 //定时器0 方式0
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