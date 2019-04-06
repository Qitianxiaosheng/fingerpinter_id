#include <stc15f2k60s2.h>			 //�������⹦�ܼĴ�����ͷ�ļ�
#include "state.h"
#include "exit.h"
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
	unsigned int i = 0;				//����ѭ������i,������ʱ
	unsigned char cnt = 0;				//�����������cnt,������λ
  Exit_Init ();
  InitLcd1602();
	

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

