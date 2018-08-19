#include "simplekey.h"
#include "sys.h"

void KEY_init(void) {
	 GPIO_InitTypeDef gpioaConfig;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 gpioaConfig.GPIO_Pin = SIMPLE_KEY1|SIMPLE_KEY2;
	 gpioaConfig.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOA,&gpioaConfig);
}
