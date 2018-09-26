#include "stm32f10x.h"
#include "lm75a.h"
#include "oled0561.h"
#include "delay.h"

int main (void){
	u8 buff[3];
	delay_ms(100);
	RCC_Configuration();
	IIC_init();
	LM75A_read(buff);
	OLED_init();
	OLED_display8x16_str(0,"  Temp:");
	while(1){
		LM75A_read(buff);
		OLED_display8x16(16,2,buff[1]/10+0x30);
	    OLED_display8x16(24,2,buff[1]%10+0x30);
		OLED_display8x16(32,2,'.');
		OLED_display8x16(40,2,buff[2]/10+0x30);
		OLED_display8x16(48,2,buff[2]%10+0x30);
		delay_ms(100);
	}	
}
