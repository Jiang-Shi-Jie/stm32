#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "simplekey.h"
#include "flash.h"


int main (void){
	u16 a;
	u32 addr;
	RCC_Configuration();
	LED_init();
	KEY_init();
	addr = FLASH_page(127,0x0000);
	a = FLASH_read(addr);
	GPIO_WriteBit(GPIOB,LED,(BitAction) a);
	while(1) {
		if(!GPIO_ReadInputDataBit(GPIOA,SIMPLE_KEY1)) {
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(GPIOA,SIMPLE_KEY1)) {
				a = 1-GPIO_ReadInputDataBit(GPIOB,LED);
				FLASH_write(addr,a);
				GPIO_WriteBit(GPIOB,LED,(BitAction) a);
				while(!GPIO_ReadInputDataBit(GPIOA,SIMPLE_KEY1));
			}
		}
    }
}
