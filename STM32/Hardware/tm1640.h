#ifndef _TM1640_H_
#define _TM1640_H_

#include "sys.h"

#define TM1640_GPIOPORT GPIOA
#define TM1640_DIN GPIO_Pin_12
#define TM1640_SCLK GPIO_Pin_11

#define TM1640_SPEED 1  //通信速度（默认1，最快）
#define TM1640_MODE 0x44  //固定地址模式
//#define TM1640_MODE 0x40  //地址加一模式

//#define TM1640_BRIGHTNESS 0x80   //关毕显示
//#define TM1640_BRIGHTNESS 0x88   //最小
//#define TM1640_BRIGHTNESS 0x89   //亮度
//#define TM1640_BRIGHTNESS 0x8a   //亮度
#define TM1640_BRIGHTNESS 0x8b   //亮度
//#define TM1640_BRIGHTNESS 0x8c   //亮度
//#define TM1640_BRIGHTNESS 0x8d   //亮度
//#define TM1640_BRIGHTNESS 0x8f   //亮度

void TM1640_init(void);
void TM1640_display(u8 addr,u8 data);
void TM1640_led(u8 data);

#endif
