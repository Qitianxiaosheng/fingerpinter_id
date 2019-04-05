#ifndef  __LCD_H_
#define __LCD_H_

/**********************************
包含头文件
**********************************/
#include <stc15f2k60s2.h>
//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P3^7;
sbit LCD1602_RW=P4^1;
sbit LCD1602_RS=P4^2;

/**********************************
函数声明
**********************************/
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat)	;
/*LCD1602初始化子程序*/		
void LcdInit();						  

#endif
