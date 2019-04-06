#ifndef __STATE_H_
#define __STATE_H_
#include "led.h"		
#include "lcd.h" 
#include "beep.h"
#include "delay.h"
#include "rtc.h"
void idle_handle(void);
void add_handle(void);
void del_handle (void);
void identify_handle(void);


#endif



