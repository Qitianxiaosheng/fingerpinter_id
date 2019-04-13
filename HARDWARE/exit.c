#include "exit.h"

/////////////
extern  flag ;
extern  id_flag;
extern  pwd_flag;
extern  idy_stop_flag;
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
			  case identify_state : flag = pwd_state;idy_stop_flag=1;break;
				case del_state : flag = add_state;      break;
				case add_state : flag = idle_state; break;
				default : flag = idle_state;
			}
		 while(!KEY1);
    }
	}
}








