#include"uart.h"

void Uart_Init(void)
{
	TMOD=0x20;       //8位定时器，自动重装计数值
	TH1=0xFD;         
	TH1=0xFD;        //波特率是9600b/s；
	TR1=1;
	SCON = 0x40;		//定时器1做串口1的波特率发生器;
}

void Uart_Send_Byte(unsigned char c)//UART Send a byte
{
    SBUF = c;
    while((SCON & 0X02) == 0);		//发送完为1
    SCON &= 0XFD;	// 把 TI 位清0   其他位保持不变
}

unsigned char Uart_Receive_Byte()//UART Receive a byteg
{
    unsigned char dat;
    while((SCON & 0X01) == 0);	 //接收完为1
    SCON &= 0XFE;	// 把 RI 位清0   其他位保持不变
    dat = SBUF;
    return (dat);
}
