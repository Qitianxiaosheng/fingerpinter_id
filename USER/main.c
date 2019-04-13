#include "state.h"//包含特殊功能寄存器的头文件
int flag=0 ;

/*******************************************************************************
* 函 数 名         :   idle_handle
* 函数功能		     : 空闲服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void main()							//主函数，每个C程序里都只有一个主函数
{									//{}代表函数的开始和结尾，注意成对存在
  u16 i;
  unsigned char PuZh[]=" Init success ";	
    TimerInit();
    Exit_Init ();
    InitLcd1602();
    Ds1302Init();
    UartInit();
  	for(i=0;i<6;i++)//开始握手6次，如果没有一次成功，表示模块通信不正常。只要成功就跳出此循环
	 {
		  delay_ms(500);
		 if(VefPSW()==1)//与模块握手通过，绿灯亮起。进入识别模式
		 {
				buzzer=0;
			  delay_ms(500);
			  buzzer=1;
				break; //成功就退出这个循环
			 
		 }	 
	 }
    LcdShowStr(0,0,PuZh);
    delay_ms(500);
    delay_ms(500);
	while(1)			   //程序在这个函数死循环
	{
		
	 
		if (flag == idle_state)
			idle_handle();
		else if (flag == identify_state)
			identify_handle();
		else if (flag == pwd_state)
			pwd_handle();
		else if (flag == err_state)
			err_handle();		
		else if (flag == del_state)
			del_handle();
		else 
			add_handle();
		
	}
}

