#include "stm32f10x.h"
#include "led.h"
#include "rtc.h"
#include "usart.h"
#include "tm1640.h"

int main (void){
	u8 buffer,sm1,sm2,sm3,sm4,sm5,sm6,sm7,sm0;
	u32 val;
	const u8 ledd[] = {0x40,0x01,0x02,0x04,0x08,0x10,0x20};
	struct DateTime datetime;
	RCC_Configuration();
	datetime.year = 2018;
	datetime.month = 8;
	datetime.day = 22;
	datetime.hour = 19;
	datetime.minute = 40;
	datetime.second = 0;
	USART1_init(115200,DISABLE);
	USART1_printf("INIT USART1");
	LED_init();
	USART1_printf("INIT LED");
	RTC_init();
	USART1_printf("INIT RTC");
	TM1640_init();
    USART1_printf("INIT TM1640");
	while(1) {
		 datetime = RTC_dateTime();
		 if(buffer != datetime.second) {
			buffer = datetime.second;
			val=RTC_GetCounter();
			USART1_printf("READ RTC[%d]\n",val);
		 	USART1_printf("%d-%d-%d %d:%d:%d (%d)\n",datetime.year,datetime.month,datetime.day,datetime.hour,datetime.minute,datetime.second,datetime.week);
			sm0 = datetime.month / 10;
			sm1 = datetime.month % 10;
			sm2 = datetime.day / 10;
			sm3 = datetime.day % 10;
			sm4 = datetime.hour / 10;
			sm5 = datetime.hour % 10;
			sm6 = datetime.minute / 10;
			sm7 = datetime.minute % 10;
			if(datetime.second%2) {
			   sm7 += 10;
			}
			TM1640_display(0,sm0);
			TM1640_display(1,sm1);
			TM1640_display(2,sm2);
			TM1640_display(3,sm3);
			TM1640_display(4,sm4);
			TM1640_display(5,sm5);
			TM1640_display(6,sm6);
			TM1640_display(7,sm7);
			TM1640_led(ledd[datetime.week]);
		 	GPIO_WriteBit(GPIOB,LED1,(BitAction)(datetime.second % 2));
			GPIO_WriteBit(GPIOB,LED2,(BitAction)(1-(datetime.second % 2)));
		 }
	}	
}