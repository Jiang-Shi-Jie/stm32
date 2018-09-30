#ifndef _RELAY_H_
#define _RELAY_H_

#include "sys.h"

#define RELAYPORT GPIOA
#define RELAY1 GPIO_Pin_14
#define RELAY2 GPIO_Pin_13

void Relay_init(void);

void setRelay1(BitAction BitVal);
void setRelay2(BitAction BitVal);
#endif
