#ifndef __LED_H_
#define __LED_H_
#include <stc15f2k60s2.h>
#include <intrins.h>

sbit red=   P0^0;//录入模式指示灯 在板子靠近单片机处
sbit green= P0^1;//识别模式指示灯 在板子远离单片机处
sbit led2 = P0^2;
sbit led3 = P0^3;
sbit led4 = P0^4;
sbit led5 = P0^5;
sbit led6 = P0^6;
sbit led7 = P0^7;
void turn_on_led(unsigned char ledn);//n=1,2,3,4,5,6,7
void turn_off_led(unsigned char ledn);//n=1,2,3,4,5,6,7

#endif