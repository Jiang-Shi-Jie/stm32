#include "tm1640.h"
#include "delay.h"

void TM1640_stop(void) {
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_RESET);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_SET);
	delay_us(TM1640_SPEED);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_SET);
	delay_us(TM1640_SPEED);
}

void TM1640_write(u8 data){
	u8 i,aa;
	aa=data;
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_RESET);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_RESET);
	for(i=0;i<8;i++){
		GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_RESET);
		delay_us(TM1640_SPEED);
		if(aa&0x01){
			GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_SET);
			delay_us(TM1640_SPEED);
		}else{
			GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_RESET);
			delay_us(TM1640_SPEED);
		}
		GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_SET);	
		delay_us(TM1640_SPEED);
		aa=aa>>1;
   }
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_RESET);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_RESET);
}


void TM1640_start(void) {
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_SET);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_SET);
	delay_us(TM1640_SPEED);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_RESET);
	delay_us(TM1640_SPEED);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_RESET);
	delay_us(TM1640_SPEED);
}

void TM1640_init(void) {
	GPIO_InitTypeDef gpioaConfig;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	gpioaConfig.GPIO_Pin = TM1640_DIN | TM1640_SCLK;
	gpioaConfig.GPIO_Speed	= GPIO_Speed_50MHz;
	gpioaConfig.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(TM1640_GPIOPORT,&gpioaConfig);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,Bit_SET);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,Bit_SET);
	TM1640_start();
	TM1640_write(TM1640_MODE);
	TM1640_stop();
	TM1640_start();
	TM1640_write(TM1640_BRIGHTNESS);
	TM1640_stop();
}

void TM1640_led(u8 data) {
	TM1640_start();
	TM1640_write(0xc8);
	TM1640_write(data);
	TM1640_stop();	
}
/**
* 8位数码管地址显示从0开始 到7止
*/
void TM1640_display(u8 addr,u8 data) {
	const u8 buff[21] = {
		0x3f,0x06,0x5b,0x4f,   //0,1,2,3
		0x66,0x6d,0x7d,0x07,   //4,5,6,7
		0x7f,0x6f,			   //8,9,
		0xbf,0x86,0xdb,0xcf,   
		0xe6,0xed,0xfd,0x87,
		0xff,0xef,
		0x00					
	};
	TM1640_start();
	TM1640_write(0xc0 + addr);
	TM1640_write(buff[data]);
	TM1640_stop();	
}
