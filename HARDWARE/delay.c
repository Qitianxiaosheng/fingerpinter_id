#include "delay.h"
#include <intrins.h>

void delay_ms(unsigned char t)//ÑÓÊ±1ms
{
  unsigned char a,i,j;
  for(a=t;a>0;a--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		}while (--i);
	}
}
void delay_us(unsigned char t)
{
	unsigned char a;
	for(a=t;a>0;a--)
	{
		_nop_();
	  _nop_();
	  _nop_();
	}
}
