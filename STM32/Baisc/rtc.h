#ifndef _RTC_H_
#define _RTC_H_

#include "sys.h"

#define BACKFLAG 0XABCD

struct DateTime {
	u16 year;
	u8 month,day,hour,minute,second,week;
};

void RTC_firstInit(void);
void RTC_init(void);
u32 getSecond(char flag,struct DateTime time);
struct DateTime parse(u32 val);
struct DateTime RTC_Get_Week(struct DateTime time);
u8 ISLeap_Year(struct DateTime time);
struct DateTime RTC_dateTime(void);
u32 RTC_Set(struct DateTime datetime);

#endif
