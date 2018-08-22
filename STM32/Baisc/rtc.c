#include "rtc.h"

void RTC_firstInit(void) {
	//使能或者失能 APB1 外设时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);
	//使能或者失能 RTC 和后备寄存器访问 
	PWR_BackupAccessCmd(ENABLE);
	//将外设 BKP 的全部寄存器重设为缺省值 
	BKP_DeInit();
	//设置外部低速晶振（LSE）
	RCC_LSEConfig(RCC_LSE_ON);
	//LSE 晶振就绪
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	//选择 LSE 作为 RTC 时钟
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	//使能或者失能 RTC 时钟 
	RCC_RTCCLKCmd(ENABLE);
	//等待近一次对 RTC 寄存器的写操作完成 	
	RTC_WaitForSynchro();
    //等待近一次对 RTC 寄存器的写操作完成 
	RTC_WaitForLastTask();
	//设置 RTC 预分频的值 
	//晶振频率(32.768KHZ)/（X+1） = 1HZ;
	RTC_SetPrescaler(32767);
	RTC_WaitForLastTask();
	//秒中断使能 
	//RTC_ITConfig(RTC_IT_SEC,ENABLE);
	//RTC_WaitForLastTask();
}

void RTC_init(void) {
	if(BKP_ReadBackupRegister(BKP_DR10) != BACKFLAG) {
		RTC_firstInit();
		BKP_WriteBackupRegister(BKP_DR10,BACKFLAG);
	} else {
		RCC_ClearFlag();
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForSynchro();	
	}
	#ifdef RTCClockOutput_Enable   
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	    PWR_BackupAccessCmd(ENABLE);   
	    BKP_TamperPinCmd(DISABLE);   
	    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
	#endif
}

u32 getSecond(char flag,struct DateTime time) {
	switch(flag) {
		case 'Y':
		return ISLeap_Year(time)?31622400:31536000;
		case 'M':
			switch(time.month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
				return 2678400;
				case 2:
				return ISLeap_Year(time)?2505600:2419200;
				case 4:
				case 6:
				case 9:
				case 11:
				return 2592000;
				default:
				return 0;
			}
		default:
		return 0;
	}
}

struct DateTime parse(u32 val) {
	u32 _second;
	struct DateTime time;
	time.year = 1970;
	time.month = 1;
	time.day = 1;
	time.hour = 0;
	time.minute = 0;
	time.second = 0;
	while(val >= 31622400 || !ISLeap_Year(time) && val >= 31536000) {
		val -= getSecond('Y',time);
		time.year++;
	}
	_second = getSecond('M',time);
	while(val >= _second) {
		val -= _second;
		time.month++;
		_second = getSecond('M',time);
	}
	time.day = (val / 86400)+1;
	val %= 86400;
	time.hour = val / 3600;
	val %= 3600;
	time.minute = val / 60;
	val %= 60;
	time.second = val;
	time = RTC_Get_Week(time);
	return time;
}

struct DateTime RTC_Get_Week(struct DateTime time) {
	u16 y;
	u8 m,d,_week;
	y = time.year;
	m = time.month;
	d = time.day;
	if(m==1||m==2) {m+=12;y--;}
    _week=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	time.week = _week==6?0:_week+1;
	return time;
}

u8 ISLeap_Year(struct DateTime time) {
	u16 year= time.year;
	if((year%4==0)&&(year%100!=0)||(year%400==0)) {
		return 1;
	} else {
		return 0;
	}
}


struct DateTime RTC_dateTime(void){
	u32 timecount=0;
	timecount=RTC_GetCounter();	
	return parse(timecount);
}  

u32 RTC_Set(struct DateTime time){
	u16 i;
	u32 result;
	struct DateTime temp_time;
	result = 0;
	for(i=1970;i<time.year;i++) {
		temp_time.year = i;
		result += getSecond('Y',temp_time);
	}
	for(i=1;i<time.month;i++) {
		temp_time.month = i;
		result += getSecond('M',temp_time);
	}
	result += (time.day-1) * 86400;
	result += time.hour * 3600;
	result += time.minute * 60;
	result += time.second;
	RTC_firstInit();
	RTC_SetCounter(result);
	BKP_WriteBackupRegister(BKP_DR10, BACKFLAG);
	RTC_WaitForLastTask();
	return result; 
}
