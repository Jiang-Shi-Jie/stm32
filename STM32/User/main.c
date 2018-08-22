#include "stm32f10x.h"
#include "led.h"
#include "touchkey.h"
#include "buzzer.h"

int main (void){
	RCC_Configuration();
	TOUCH_KEY_init();
	LED_init();
	BUZZER_init();
	while(1) {
	   	if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_A)) {
			GPIO_WriteBit(GPIOB,LED,(BitAction)(1-GPIO_ReadInputDataBit(GPIOB,LED)));
			BUZZER_play(300,1000);
		}
		if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_B)) {
			GPIO_WriteBit(GPIOB,LED,Bit_SET);
			BUZZER_play(300,1500);
		}
		if(!GPIO_ReadInputDataBit(GPIOA,TOUCHKEY_C)) {
			GPIO_WriteBit(GPIOB,LED,Bit_RESET);
			BUZZER_play(300,2000);
		}
	}		
}
