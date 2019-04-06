#include "state.h"//包含特殊功能寄存器的头文件
int flag ;

/*******************************************************************************
* 函 数 名         :   idle_handle
* 函数功能		     : 空闲服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void main()							//主函数，每个C程序里都只有一个主函数
{									//{}代表函数的开始和结尾，注意成对存在

  unsigned char PuZh[]=" Init success ";	
  Exit_Init ();
  InitLcd1602();
  Ds1302Init();
	Uart_Init();
	LcdShowStr(0,0,PuZh);
  delay_ms(500);
  delay_ms(500);

	while(1)			   //程序在这个函数死循环
	{
		if (flag == idle_state)
			idle_handle();
		else if (flag == identify_state)
			identify_handle();
		else if (flag == del_state)
			del_handle();
		else 
			add_handle();
	}
}

