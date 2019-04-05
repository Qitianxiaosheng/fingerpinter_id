#ifndef __LED_H_
#define __LED_H_
#include <stc15f2k60s2.h>

sbit led0 = P0^0;
sbit led1 = P0^1;
sbit led2 = P0^2;
sbit led3 = P0^3;
sbit led4 = P0^4;
sbit led5 = P0^5;
sbit led6 = P0^6;
sbit led7 = P0^7;
void turn_on_led(unsigned char ledn);//n=1,2,3,4,5,6,7
void turn_off_led(unsigned char ledn);//n=1,2,3,4,5,6,7

#endif