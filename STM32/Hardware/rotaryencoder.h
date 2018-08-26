#ifndef _ROTARYENCODER_H_
#define _ROTARYENCODER_H_

#include "sys.h"

#define ENCODER_PORTA GPIOA
#define ENCODER_L GPIO_Pin_6
#define ENCODER_D GPIO_Pin_7

#define ENCODER_PORTB GPIOB
#define ENCODER_R GPIO_Pin_2

void ENCODER_init(void);
u8 ENCODER_read(void);

#endif
