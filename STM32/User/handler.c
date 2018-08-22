#include "handler.h"

//RTC���ж�
void RTC_IRQHandler(void) {
	if(RTC_GetITStatus(RTC_IT_SEC) != RESET) {
	
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);
	RTC_WaitForLastTask();
}

//RTC�����ж�
void RTCAlarm_IRQHandler(void) {
	if(RTC_GetITStatus(RTC_FLAG_ALR) != RESET) {
	
	}
	RTC_ClearITPendingBit(RTC_FLAG_ALR);
	RTC_WaitForLastTask();
}