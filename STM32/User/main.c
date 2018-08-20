#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "simplekey.h"
#include "buzzer.h"
#include "usart.h"

int main (void){
	RCC_Configuration();
	LED_init();
	KEY_init();
	BUZZER_init();
	USART1_init(115200);
	BUZZER_play(300,554);
	while(1) {
		if(!GPIO_ReadInputDataBit(GPIOA,SIMPLE_KEY1)) {
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(GPIOA,SIMPLE_KEY1)) {
				BUZZER_play(300,1000);
				GPIO_WriteBit(GPIOB,LED,(BitAction)(1-GPIO_ReadInputDataBit(GPIOB,LED)));
				USART1_printf("hello%s\n","world");
				while(!GPIO_ReadInputDataBit(GPIOA,SIMPLE_KEY1));
			}
		}
    }
}
