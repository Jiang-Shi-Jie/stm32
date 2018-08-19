#include "buzzer.h"
#include "delay.h"

void BUZZER_init(void) {
	 GPIO_InitTypeDef gpiobConfig;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 gpiobConfig.GPIO_Pin = BUZZER;
	 gpiobConfig.GPIO_Speed	= GPIO_Speed_50MHz;
	 gpiobConfig.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOB,&gpiobConfig);
	 GPIO_WriteBit(GPIOB,BUZZER,(BitAction)(1));
}

void BUZZER_play(u16 len,u32 hz) {
	u16 i;
	u32 time = 500000/hz;
	for(i=0;i<len;i++) {
		GPIO_WriteBit(GPIOB,BUZZER,(BitAction)0);
		delay_us(time);
		//最后将输出低电平
		GPIO_WriteBit(GPIOB,BUZZER,(BitAction)1);
		delay_us(time);
	}
}
