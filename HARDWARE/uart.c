#include"uart.h"

void Uart_Init(void)
{
	TMOD=0x20;       //8λ��ʱ�����Զ���װ����ֵ
	TH1=0xFD;         
	TH1=0xFD;        //��������9600b/s��
	TR1=1;
	SCON = 0x40;		//��ʱ��1������1�Ĳ����ʷ�����;
}

void Uart_Send_Byte(unsigned char c)//UART Send a byte
{
    SBUF = c;
    while((SCON & 0X02) == 0);		//������Ϊ1
    SCON &= 0XFD;	// �� TI λ��0   ����λ���ֲ���
}

unsigned char Uart_Receive_Byte()//UART Receive a byteg
{
    unsigned char dat;
    while((SCON & 0X01) == 0);	 //������Ϊ1
    SCON &= 0XFE;	// �� RI λ��0   ����λ���ֲ���
    dat = SBUF;
    return (dat);
}
