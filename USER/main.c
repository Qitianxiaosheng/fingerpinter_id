#include "led.h"		 //包含特殊功能寄存器的头文件

sbit led8 = P0^2;					 //位地址声明，sbit是小写，P是大写
//---------------------------------------------------------------
//主函数
void main()							//主函数，每个C程序里都只有一个主函数
{									//{}代表函数的开始和结尾，注意成对存在

	led8 = 0;						//每个分好代表一个语句的结束

}