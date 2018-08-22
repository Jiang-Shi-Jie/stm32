#include "stm32f10x.h"
#include "led.h"
#include "rtc.h"
#include "usart.h"


int main (void){
	u8 buffer;
	u32 val;
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
	while(1) {
		 datetime = RTC_dateTime();
		 if(buffer != datetime.second) {
			buffer = datetime.second;
			val=RTC_GetCounter();
		 	USART1_printf("%d-%d-%d %d:%d:%d (%d)\n",datetime.year,datetime.month,datetime.day,datetime.hour,datetime.minute,datetime.second,datetime.week);
		 	GPIO_WriteBit(GPIOB,LED,(BitAction)(datetime.second % 2));
		 }
	}	
}
