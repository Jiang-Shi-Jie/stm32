#ifndef _OLED0561_H_
#define _OLED0561_H_

#include "sys.h"

#define OLED0561_ADDR 0x78
#define CON 0x00   //Ö¸Áî
#define DAT 0x40   //Êý¾Ý

void OLED_init(void);
void OLED_display_on(void);
void OLED_display_off(void);
void OLED_display_clear(void);

void OLED_display8x16(u8 x,u8 y,u8 ind);
void OLED_display8x16_str(u8 row,u8 *str);
void OLED_display16x16(u8 x,u8 y,u16 Ind);
void OLED_display128x64(const unsigned char img[1024]);

#endif
