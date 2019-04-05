#include "exit.h"
#include "key.h" 
#include "delay.h"
/////////////
extern  flag ;
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
	IT1=1;
	EX1=1;
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
				case add_state : flag = identify_state; break;
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
void INT1_ISR() interrupt 2
{
	if(KEY2==0)
	{	
		delay_ms(10);
		if(KEY2 == 0)
		{
		 flag = idle_state;
		 while(!KEY2);
    }
	}
}
