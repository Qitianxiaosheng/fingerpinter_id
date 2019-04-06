#include "state.h"

/*******************************************************************************
* 函 数 名         :   idle_handle
* 函数功能		     : 空闲服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void idle_handle(void)
{
 
  u8 stat[]=" IDLE_STATE";
  Lcd1602_Write_Cmd(0x01); //清屏
  LcdShowStr(0,0,stat);
  Ds1302ReadTime();
	DisplayOneChar(1,1,'0'+TIME[4]/16);			//月
	DisplayOneChar(2,1,'0'+(TIME[4]&0x0f));
	DisplayOneChar(3,1,'-');
	DisplayOneChar(4,1,'0'+TIME[3]/16);			//日
	DisplayOneChar(5,1,'0'+(TIME[3]&0x0f));
	DisplayOneChar(6,1,'-');
	DisplayOneChar(7,1,'0'+TIME[2]/16);				//时
	DisplayOneChar(8,1,'0'+(TIME[2]&0x0f));				 
	DisplayOneChar(9,1,'-');
	DisplayOneChar(10,1,'0'+TIME[1]/16);				//分
	DisplayOneChar(11,1,'0'+(TIME[1]&0x0f));	
	DisplayOneChar(12,1,'-');
	DisplayOneChar(13,1,'0'+TIME[0]/16);				//秒
	DisplayOneChar(14,1,'0'+(TIME[0]&0x0f));
  delay_ms(50);
	no_speaker();	  
}
/*******************************************************************************
* 函 数 名         :   add_handle
* 函数功能		     : 添加指纹服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void add_handle(void)
{
	unsigned char stat[]=" ADD_STATE";
  Lcd1602_Write_Cmd(0x01); //清屏
  LcdShowStr(0,0,stat);
  delay_ms(50);
	no_speaker();	 
}
/*******************************************************************************
* 函 数 名         :   del_handle
* 函数功能		     : 删除指纹服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void del_handle (void)
{
	unsigned char stat[]="DLE_STATE";
	Lcd1602_Write_Cmd(0x01); //清屏
  LcdShowStr(0,0,stat);
  delay_ms(50);
  no_speaker();	 
}
/*******************************************************************************
* 函 数 名         :   identify_handle
* 函数功能		     : 识别指纹服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void identify_handle(void)
{
	unsigned char stat[]="IFY_STATE";
	Lcd1602_Write_Cmd(0x01); //清屏
  LcdShowStr(0,0,stat);
  delay_ms(50);
  success_speaker();
}









