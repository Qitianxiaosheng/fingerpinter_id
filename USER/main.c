#include "state.h"//�������⹦�ܼĴ�����ͷ�ļ�
int flag=0 ;

/*******************************************************************************
* �� �� ��         :   idle_handle
* ��������		     : ���з�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void main()							//��������ÿ��C�����ﶼֻ��һ��������
{									//{}�������Ŀ�ʼ�ͽ�β��ע��ɶԴ���
  u16 i;
  unsigned char PuZh[]=" Init success ";	
    TimerInit();
    Exit_Init ();
    InitLcd1602();
    Ds1302Init();
    UartInit();
  	for(i=0;i<6;i++)//��ʼ����6�Σ����û��һ�γɹ�����ʾģ��ͨ�Ų�������ֻҪ�ɹ���������ѭ��
	 {
		  delay_ms(500);
		 if(VefPSW()==1)//��ģ������ͨ�����̵����𡣽���ʶ��ģʽ
		 {
				buzzer=0;
			  delay_ms(500);
			  buzzer=1;
				break; //�ɹ����˳����ѭ��
			 
		 }	 
	 }
    LcdShowStr(0,0,PuZh);
    delay_ms(500);
    delay_ms(500);
	while(1)			   //���������������ѭ��
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

