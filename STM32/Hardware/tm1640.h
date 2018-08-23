#ifndef _TM1640_H_
#define _TM1640_H_

#include "sys.h"

#define TM1640_GPIOPORT GPIOA
#define TM1640_DIN GPIO_Pin_12
#define TM1640_SCLK GPIO_Pin_11

#define TM1640_SPEED 1  //ͨ���ٶȣ�Ĭ��1����죩
#define TM1640_MODE 0x44  //�̶���ַģʽ
//#define TM1640_MODE 0x40  //��ַ��һģʽ

//#define TM1640_BRIGHTNESS 0x80   //�ر���ʾ
//#define TM1640_BRIGHTNESS 0x88   //��С
//#define TM1640_BRIGHTNESS 0x89   //����
//#define TM1640_BRIGHTNESS 0x8a   //����
#define TM1640_BRIGHTNESS 0x8b   //����
//#define TM1640_BRIGHTNESS 0x8c   //����
//#define TM1640_BRIGHTNESS 0x8d   //����
//#define TM1640_BRIGHTNESS 0x8f   //����

void TM1640_init(void);
void TM1640_display(u8 addr,u8 data);
void TM1640_led(u8 data);

#endif
