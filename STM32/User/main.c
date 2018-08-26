#include "stm32f10x.h"
#include "led.h"
#include "rtc.h"
#include "usart.h"
#include "tm1640.h"
#include "rotaryencoder.h"
#include "delay.h"

int main (void){
	u8 encoder,sm0,sm1,sm2;
	u16 time;
	time = 0;
	RCC_Configuration();
	TM1640_init();
	USART1_init(115200,DISABLE);
	ENCODER_init();
	USART1_printf("%s","init success");
	while(1) {
		 encoder = 	ENCODER_read();
		 if(encoder == 2 && time > 0) {
		 	 time -= 5;
		 }
		 if(encoder ==1 && time <500) {
		 	 time += 5;
		 }
		 if(encoder == 10) {
		 	 time = 0;
		 }
		 if(encoder != 0) {
		 	 USART1_printf("%d",encoder);
		 }
		 sm0 = time / 100;
		 sm1 = (time / 10) % 10;
		 sm2 = time % 10;
		 TM1640_display(0,sm0);
		 TM1640_display(1,sm1);
		 TM1640_display(2,sm2);
		 TM1640_display(3,20);
		 TM1640_display(4,20);
		 TM1640_display(5,20);
		 TM1640_display(6,20);
		 TM1640_display(7,20);
	}	
}
