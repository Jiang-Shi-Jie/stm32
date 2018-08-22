#include "touchkey.h"

void TOUCH_KEY_init(void) {
	 GPIO_InitTypeDef gpiobConfig;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 gpiobConfig.GPIO_Pin = TOUCHKEY_A|TOUCHKEY_B|TOUCHKEY_C|TOUCHKEY_D;
	 gpiobConfig.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOA,&gpiobConfig);
}
