#include "uart.h"
/*************	���س�������	**************/
#define MAIN_Fosc		11059200L	//������ʱ��
#define	RX1_Lenth		32			//���ڽ��ջ��峤��
#define	BaudRate1		115200UL	//ѡ������


#define	Timer1_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 1 ��װֵ�� ��Ӧ300KHZ
#define	Timer2_Reload	(65536UL -(MAIN_Fosc / 4 / BaudRate1))		//Timer 2 ��װֵ�� ��Ӧ300KHZ



void UsartInit(void)
{
SCON  = (SCON & 0x3f) | 0x40;				//8λ����
	P_SW1 &= ~0xc0;		//UART1 ʹ��P30 P31��	Ĭ��

	AUXR &= ~(1<<4);	//Timer stop		������ʹ��Timer2����
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	T2H = (u8)(Timer2_Reload >> 8);
	T2L = (u8)Timer2_Reload;
	AUXR |=  (1<<4);	//Timer run enable

	REN = 1;	//�������
	ES  = 1;	//�����ж�

	EA = 1;		//����ȫ���ж�
}


/********************* UART1�жϺ���************************/
void Usart() interrupt 4
{	
	u8 receiveData;

	receiveData=SBUF;//��ȥ���յ�������
	RI = 0;//��������жϱ�־λ
	SBUF=receiveData;//�����յ������ݷ��뵽���ͼĴ���
	while(!TI);			 //�ȴ������������
	TI=0;						 //���������ɱ�־λ
}
