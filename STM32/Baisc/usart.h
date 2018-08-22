#ifndef _USART_H_
#define _USART_H_

#define USART_REC_LEN 256

#include "sys.h"

void USART1_init(u32 speed,FunctionalState NewState);
void USART1_send_char(u8 data);
void USART1_printf (char *fmt, ...);

#endif
