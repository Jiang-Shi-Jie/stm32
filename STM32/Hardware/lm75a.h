#ifndef _LM75A_H_
#define _LM75A_H_

#include "sys.h"
#include "iic.h"

#define LM75A_ADDR 0X9E

void LM75A_read(u8 *Tempbuffer);
//µôµçÄ£Ê½ 
void LM75A_powerDown(void);

#endif
