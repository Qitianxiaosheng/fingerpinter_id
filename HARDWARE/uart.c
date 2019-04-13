#include "uart.h"
#include "delay.h"


void UartInit(void)		//57600bps@11.0592MHz
{

	AUXR &= ~(1<<4);	//Timer stop		波特率使用Timer2产生
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	T2H = (unsigned char)(Timer2_Reload >> 8);
	T2L = (unsigned char)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable

	S2CON |= 0x10;	//允许接收
//	IE2 |= 0x01;	//允许中断

//	EA = 1;		//允许全局中断
}

void TxdByte(unsigned char dat)//串口发送信息,通过查询方式发送一个字符
{
    S2BUF = dat;	 //读入数据
    while(!S2CON&0x02);	 //等待发送完毕
	  delay_us(10);
    S2CON &= 0xfd;		 //清零
	  delay_us(20);
}