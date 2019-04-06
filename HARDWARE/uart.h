#ifndef _UART_H_
#define _UART_H_

#include <STC15F2K60S2.H>//P3^1 Tx , P3^0Rx

void Uart_Init(void);
void Uart_Send_Byte(unsigned char c);
unsigned char Uart_Receive_Byte();

#endif