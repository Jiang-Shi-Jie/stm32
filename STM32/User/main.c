#include "stm32f10x.h"
#include "tm1640.h"
#include "lm75a.h"

int main (void){
	u8 buff[3];
	RCC_Configuration();
	IIC_init();
	TM1640_init();
	TM1640_display(0,20);
	TM1640_display(1,20);
	TM1640_display(2,20);
	TM1640_display(3,20);
	TM1640_display(4,20);
	TM1640_display(5,20);
	TM1640_display(6,20);
	TM1640_display(7,20);
	while(1) {
		LM75A_read(buff);
		TM1640_display(1,buff[1]/10);
		TM1640_display(2,buff[1]%10+10);
		TM1640_display(3,buff[2]/10);
		TM1640_display(4,buff[2]%10);	
	}	
}
