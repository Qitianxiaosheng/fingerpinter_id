#include "state.h"//�������⹦�ܼĴ�����ͷ�ļ�
int flag ;

/*******************************************************************************
* �� �� ��         :   idle_handle
* ��������		     : ���з�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void main()							//��������ÿ��C�����ﶼֻ��һ��������
{									//{}�������Ŀ�ʼ�ͽ�β��ע��ɶԴ���

  unsigned char PuZh[]=" Init success ";	
  Exit_Init ();
  InitLcd1602();
  Ds1302Init();
	Uart_Init();
	LcdShowStr(0,0,PuZh);
  delay_ms(500);
  delay_ms(500);

	while(1)			   //���������������ѭ��
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

