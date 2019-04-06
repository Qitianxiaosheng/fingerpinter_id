#include "state.h"

/*******************************************************************************
* �� �� ��         :   idle_handle
* ��������		     : ���з�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void idle_handle(void)
{
 
  u8 stat[]=" IDLE_STATE";
  Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
  Ds1302ReadTime();
	DisplayOneChar(1,1,'0'+TIME[4]/16);			//��
	DisplayOneChar(2,1,'0'+(TIME[4]&0x0f));
	DisplayOneChar(3,1,'-');
	DisplayOneChar(4,1,'0'+TIME[3]/16);			//��
	DisplayOneChar(5,1,'0'+(TIME[3]&0x0f));
	DisplayOneChar(6,1,'-');
	DisplayOneChar(7,1,'0'+TIME[2]/16);				//ʱ
	DisplayOneChar(8,1,'0'+(TIME[2]&0x0f));				 
	DisplayOneChar(9,1,'-');
	DisplayOneChar(10,1,'0'+TIME[1]/16);				//��
	DisplayOneChar(11,1,'0'+(TIME[1]&0x0f));	
	DisplayOneChar(12,1,'-');
	DisplayOneChar(13,1,'0'+TIME[0]/16);				//��
	DisplayOneChar(14,1,'0'+(TIME[0]&0x0f));
  delay_ms(50);
	no_speaker();	  
}
/*******************************************************************************
* �� �� ��         :   add_handle
* ��������		     : ���ָ�Ʒ�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void add_handle(void)
{
	unsigned char stat[]=" ADD_STATE";
  Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
  delay_ms(50);
	no_speaker();	 
}
/*******************************************************************************
* �� �� ��         :   del_handle
* ��������		     : ɾ��ָ�Ʒ�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void del_handle (void)
{
	unsigned char stat[]="DLE_STATE";
	Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
  delay_ms(50);
  no_speaker();	 
}
/*******************************************************************************
* �� �� ��         :   identify_handle
* ��������		     : ʶ��ָ�Ʒ�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void identify_handle(void)
{
	unsigned char stat[]="IFY_STATE";
	Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
  delay_ms(50);
  success_speaker();
}









