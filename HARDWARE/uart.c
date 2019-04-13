#include "uart.h"
#include "delay.h"


void UartInit(void)		//57600bps@11.0592MHz
{

	AUXR &= ~(1<<4);	//Timer stop		������ʹ��Timer2����
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	T2H = (unsigned char)(Timer2_Reload >> 8);
	T2L = (unsigned char)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable

	S2CON |= 0x10;	//�������
//	IE2 |= 0x01;	//�����ж�

//	EA = 1;		//����ȫ���ж�
}

void TxdByte(unsigned char dat)//���ڷ�����Ϣ,ͨ����ѯ��ʽ����һ���ַ�
{
    S2BUF = dat;	 //��������
    while(!S2CON&0x02);	 //�ȴ��������
	  delay_us(10);
    S2CON &= 0xfd;		 //����
	  delay_us(20);
}