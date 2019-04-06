#include "exit.h"

/////////////
extern  flag ;
extern  id_flag;
/*******************************************************************************
* �� �� ��         :   Exit_Init
* ��������		     : �ⲿ�жϳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �����жϷ�ʽ���Ҵ��ⲿ�ж�1��2��
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
* �� �� ��         :   INT0_ISR
* ��������		     : �ⲿ�ж�0������
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
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
* �� �� ��         :   INT1_ISR
* ��������		     : �ⲿ�ж�1������
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵΪ��ʼֵ
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



