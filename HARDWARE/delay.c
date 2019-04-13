#include "delay.h"
#include <intrins.h>
/*******************************************************************************
* 函 数 名         :   delay_ms
* 函数功能		     : 延时函数，延时1ms
* 输    入         : t
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/

void delay_ms(unsigned char t)//延时ms
{
	unsigned char i, j;
  int k;
	for(k=0;k<t;k++)
	{
	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
 }
}
/*******************************************************************************
* 函 数 名         :  delay_us
* 函数功能		     : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/
void delay_us(unsigned char t)//延时us
{
	unsigned char a;
	for(a=t;a>0;a--)
	{
		_nop_();
	  _nop_();
	  _nop_();
	}
}
