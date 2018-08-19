#ifndef _FLASH_C_
#define _FLASH_C_

#include "sys.h"

void FLASH_write(u32 addr,u16 data);
u32 FLASH_page(u16 page,u16 offset);
u16 FLASH_read(u32 addr);

#endif
