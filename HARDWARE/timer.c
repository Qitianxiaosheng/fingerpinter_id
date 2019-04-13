#include "timer.h"

unsigned int clk0=0;
void  TimerInit(void)
{
	ET0=1;     //定时器0开中断
	TL0=0x97;  //17ms的初值
	TH0=0xBD;
  TR0=1;// 开定时器0	
	
}
void  Timer0(void) interrupt 1//定时器0中断函数
{
 	TL0=0x97;
	TH0=0xBD;
	clk0++;   //延时17ms
}


