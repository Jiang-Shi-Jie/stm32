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
* ���ر�������״̬
* �������1�򷵻�1 ����2����2
* �����ת��ʱ�򰴼��а����򷵻�11��12
*/
u8 ENCODER_read(void) {
	u8 result,kFlag;
	u16 count;
	result = 0;
	//���û����������ô��KUP��0
	if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L)) {KUP = 0;}
	if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L) && KUP == 0) {
		delay_us(100);
		kFlag = GPIO_ReadInputDataBit(ENCODER_PORTB,ENCODER_R);
		delay_ms(3);  //��ʱȥ�趶
		if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_L)) {
			if(kFlag == 0) {
				result = 1;
			} else {
				result = 2;
			}
			//�ȴ������ĶϿ�
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
	//���ϰ�����״̬
	if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_D) && KUP==0) {
		 delay_ms(20);
		 if(!GPIO_ReadInputDataBit(ENCODER_PORTA,ENCODER_D)) {
		 	result += 10;
		 }
	}
	return result;
}
