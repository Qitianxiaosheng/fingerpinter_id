#ifndef  __LCD_H_
#define __LCD_H_

/**********************************
����ͷ�ļ�
**********************************/
#include <stc15f2k60s2.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P3^7;
sbit LCD1602_RW=P4^1;
sbit LCD1602_RS=P4^2;

/**********************************
��������
**********************************/
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  

#endif
