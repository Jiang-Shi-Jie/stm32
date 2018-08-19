#ifndef _BUZZER_H_
#define _BUZZER_H_

#define BUZZER GPIO_Pin_5

#include "sys.h"

void BUZZER_init(void);
void BUZZER_play(u16 len,u32 hz);

#endif
