#include "exit.h"

/////////////
extern  flag ;
extern  id_flag;
/*******************************************************************************
* 函 数 名         :   Exit_Init
* 函数功能		     : 外部中断初始化
* 输    入         : 无
* 输    出         : 无
* 说    名         : 设置中断方式，且打开外部中断1，2。
*******************************************************************************/
void Exit_Init (void)
	
{
	IT0=1;	
  EX0=1;
//	IT1=1;
//	EX1=1;
	EA=1;
}
/*******************************************************************************
* 函 数 名         :   INT0_ISR
* 函数功能		     : 外部中断0服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void INT0_ISR(void) interrupt 0
{
  if(KEY1==0)
	{	
		delay_ms(10);
		if(KEY1==0)
		{
			switch(flag)
			{	
				case idle_state : flag = identify_state; break;
			  case identify_state : flag = del_state; break;
				case del_state : flag = add_state;      break;
				case add_state : flag = idle_state; break;
				default : flag = idle_state;
			}
		 while(!KEY1);
    }
	}
}
/*******************************************************************************
* 函 数 名         :   INT1_ISR
* 函数功能		     : 外部中断1服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值为初始值
*******************************************************************************/
//void INT1_ISR() interrupt 2
//{
//	if(KEY2==0)
//	{	
//		delay_ms(10);
//		if(KEY2 == 0)
//		{
//		 switch(id_flag)
//			{	
//				case id_000 : id_flag = id_001; break;
//			  case id_001 : id_flag = id_002; break;
//				case id_002 : id_flag = id_000; break;
//				default : id_flag = id_000;
//			}
//		 while(!KEY2);
//    }
//	}
//}



