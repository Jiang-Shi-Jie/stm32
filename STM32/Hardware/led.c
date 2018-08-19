#include "led.h"


 void LED_init(void) {
 	//结构体初始化B组商品
	 GPIO_InitTypeDef gpiobConfig;
	 //开始GPIOB组功能
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 gpiobConfig.GPIO_Pin = LED;
	 gpiobConfig.GPIO_Speed	= GPIO_Speed_50MHz;
	 gpiobConfig.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOB,&gpiobConfig);
 }
