#ifndef __EXIT_H_
#define __EXIT_H_
#include <stc15f2k60s2.h>
#include "key.h" 
#include "delay.h"
#define idle_state 0
#define identify_state 1
#define pwd_state 2
#define err_state 3
#define del_state 4
#define add_state 5

#define id_000 4
#define id_001 5
#define id_002 6
#define clear_all 7
void Exit_Init (void);






#endif