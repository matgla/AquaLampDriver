#include "rtc/rtc.hpp"

#include <cstdio>
#include <ctime>

#include "stm32f10x_conf.h"

namespace rtc
{

Rtc::Rtc()
{
    init();
}

void Rtc::init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    BKP_DeInit();
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
    }

    /* Select LSE as RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

void Rtc::setTime(u32 day, u32 month, u32 year, u32 hours, u32 minutes, u32 seconds)
{
    std::tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hours;
    t.tm_min = minutes;
    t.tm_sec = seconds;
    time_t timeSinceEpoch = mktime(&t);
    RTC_WaitForLastTask();
    //printf("Set time to: %d\n", timeSinceEpoch);
    RTC_SetCounter(timeSinceEpoch);
    RTC_WaitForLastTask();
}

u32 Rtc::getTime()
{
    return RTC_GetCounter();
}

} // namespace rtc
