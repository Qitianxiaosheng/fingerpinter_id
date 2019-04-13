#ifndef __UART_H_
#define __UART_H_
#include <stc15f2k60s2.h>

#define MAIN_Fosc		11059200L	//定义主时钟
#define	RX1_Lenth		32			//串口接收缓冲长度
#define	BaudRate1		57600UL	//选择波特率


#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 重装值， 对应300KHZ
#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 重装值， 对应300KHZ

void UartInit(void);
void TxdByte(unsigned char dat);

#endif