#ifndef __FPM_H_
#define __FPM_H_
#include "stc15f2k60s2.h"
#include "beep.h"
#include "led.h"
#include "uart.h"
#include "delay.h"
#include "timer.h"


extern unsigned char 	SaveNumber,searchnum;
extern unsigned int  	SearchNumber;		
extern bit changeflag,modeflag,clearallflag;  //默认为识别模式，如果为1为录入指纹模式,每录入一次SaveNumber++


//////////////////////////////////////宏定义////////////////////////////////////////////////////////////////////////
#define FALSE 0
#define TURE  1

//状态定义表
#define on    	1
#define off   	0

#define MAX_NUMBER    63 
//////////////////////////////////////宏定义------------结束////////////////////////////////////////////////////////


unsigned char send_command( unsigned char *p);
bit Command(unsigned char *p,unsigned char MaxTime);
bit VefPSW(void);
void Clear_All(void);
void Clear_ONE(u8 num);
unsigned char ImgProcess(unsigned char BUFID);
bit Searchfinger(void);
unsigned char search(void);
bit savefingure(unsigned char ID);
unsigned char enroll(void);


#endif










