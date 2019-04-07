#include "uart.h"
/*************	本地常量声明	**************/
#define MAIN_Fosc		11059200L	//定义主时钟
#define	RX1_Lenth		32			//串口接收缓冲长度
#define	BaudRate1		115200UL	//选择波特率


#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 重装值， 对应300KHZ
#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 重装值， 对应300KHZ



void UsartInit(void)
{
SCON  = (SCON & 0x3f) | 0x40;				//8位数据
	P_SW1 &= ~0xc0;		//UART1 使用P30 P31口	默认

	AUXR &= ~(1<<4);	//Timer stop		波特率使用Timer2产生
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	T2H = (u8)(Timer2_Reload >> 8);
	T2L = (u8)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable

	REN = 1;	//允许接收
	ES  = 1;	//允许中断

	EA = 1;		//允许全局中断
}


/********************* UART1中断函数************************/
void Usart() interrupt 4
{	
	u8 receiveData;

	receiveData=SBUF;//出去接收到的数据
	RI = 0;//清除接收中断标志位
	SBUF=receiveData;//将接收到的数据放入到发送寄存器
	while(!TI);			 //等待发送数据完成
	TI=0;						 //清除发送完成标志位
}
