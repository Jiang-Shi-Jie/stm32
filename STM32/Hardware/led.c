#include "led.h"


 void LED_init(void) {
 	//�ṹ���ʼ��B��˿�
	 GPIO_InitTypeDef gpiobConfig;
	 //��ʼGPIOB�鹦��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 gpiobConfig.GPIO_Pin = LED1 | LED2;
	 gpiobConfig.GPIO_Speed	= GPIO_Speed_50MHz;
	 gpiobConfig.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOB,&gpiobConfig);
 }
