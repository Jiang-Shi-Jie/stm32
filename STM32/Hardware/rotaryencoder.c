#include "rotaryencoder.h"
#include "delay.h"

 u8 KUP;

void ENCODER_init(void) {
	  GPIO_InitTypeDef gpioConfig;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	  gpioConfig.GPIO_Pin = ENCODER_L | ENCODER_D;
	  gpioConfig.GPIO_Mode = GPIO_Mode_IPU;
	  GPIO_Init(ENCODER_PORTA,&gpioConfig);
	  gpioConfig.GPIO_Pin = ENCODER_R;
 	  GPIO_Init(ENCODER_PORTB,&gpioConfig);
}

/**
* 返回编码器的状态
* 如果方向1则返回1 方向2返回2
* 如果旋转的时候按键有按下则返回11或12
*/
u8 ENCODER_read(void) {
	u8 result,kFlag;
	u16 count;
	result = 0;
	//如果没有锁死，那么将KUP置0
	if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L)) {KUP = 0;}
	if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L) && KUP == 0) {
		delay_us(100);
		kFlag = GPIO_ReadInputDataBit(ENCODER_PORTB,ENCODER_R);
		delay_ms(3);  //延时去拌抖
		if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L)) {
			if(kFlag == 0) {
				result = 1;
			} else {
				result = 2;
			}
			//等待按键的断开
			count = 0;
			while((!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L)
				|| !GPIO_ReadInputDataBit(ENCODER_PORTB,ENCODER_R))
				&& 	count < 60000) {
				delay_us(20);
				count ++;
				KUP = 1;
			}
		}
	}
	//加上按键的状态
	if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_D) && KUP==0) {
		 delay_ms(20);
		 if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_D)) {
		 	result += 10;
		 }
	}
	return result;
}
