#ifndef _TOUCHKEY_H_
#define _TOUCHKEY_H_

#include "sys.h"

#define TOUCHKEY_A GPIO_Pin_0
#define TOUCHKEY_B GPIO_Pin_1
#define TOUCHKEY_C GPIO_Pin_2
#define TOUCHKEY_D GPIO_Pin_3

void TOUCH_KEY_init(void);

#endif
