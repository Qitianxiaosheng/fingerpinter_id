#include "key_arr.h"
int KeyValue;
//用来存放读取到的键值
#define GPIO_KEY P3
void KeyDown(void)
{
	char a;
  int t,g;
	
	GPIO_KEY|=0X60;
	GPIO_KEY&=0xe7;
	t=GPIO_KEY&0x60;
	if(t!=0x60)
	{ 
		 
		if(t!=0x60)
		{
			//测试列
 			delay_ms(10);//消抖
			switch(t)
			{
				case(0X40):	KeyValue=1;break;
				case(0X20):	KeyValue=2;break;
			}
			//测试行
			 GPIO_KEY&=0X9f;
	     GPIO_KEY|=0x18;
			delay_ms(10);
			g=GPIO_KEY&0x18;
			switch(g)
			{
				case(0X08):	KeyValue=KeyValue;break;
				case(0X10):	KeyValue=KeyValue+2;break;
			}
			while((a<50)&&(GPIO_KEY&0x18!=0x18))	 //检测按键松手检测
			{
				
				delay_ms(10);
				a++;
			}
			a=0;
		}
	}
}