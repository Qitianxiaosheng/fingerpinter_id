#ifndef __UART_H_
#define __UART_H_
#include <stc15f2k60s2.h>

#define MAIN_Fosc		11059200L	//������ʱ��
#define	RX1_Lenth		32			//���ڽ��ջ��峤��
#define	BaudRate1		57600UL	//ѡ������


#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 ��װֵ�� ��Ӧ300KHZ
#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 ��װֵ�� ��Ӧ300KHZ

void UartInit(void);
void TxdByte(unsigned char dat);

#endif