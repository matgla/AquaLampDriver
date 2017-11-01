#include "rtc/rtc.hpp"

#include <cstdio>
#include <ctime>
#include <functional>

#include "stm32f10x_conf.h"

namespace rtc
{

static std::function<void()> timerCallback_ = nullptr;
static std::function<void()> secondsHandler_ = nullptr;

u32 alarmTime_;
bool alarmEnabled_ = false;
Rtc::Rtc()
{
    alarmEnabled_ = false;
    init();
}

void Rtc::setHandler(std::function<void()> handler)
{
    timerCallback_ = handler;
}

void Rtc::setSecondsHandler(std::function<void()> handler)
{
    secondsHandler_ = handler;
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

    NVIC_InitTypeDef nvic;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    nvic.NVIC_IRQChannel = RTC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
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
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_WaitForLastTask();

    RTC_SetCounter(timeSinceEpoch);
    RTC_WaitForLastTask();
}

void Rtc::setAlarm(u32 time)
{
    alarmEnabled_ = true;
    alarmTime_ = time;
}

u32 Rtc::alarmTime()
{
    return alarmTime_;
}

void Rtc::fire()
{
    if (alarmEnabled_)
    {
        alarmEnabled_ = false;

        if (timerCallback_)
        {
            timerCallback_();
        }
    }
}

u32 Rtc::getTime()
{
    return RTC_GetCounter();
}


extern "C" {
void RTC_IRQHandler();
}

void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
    {
        if (secondsHandler_)
        {
            secondsHandler_();
        }
        if (RTC_GetCounter() >= Rtc::alarmTime())
        {
            Rtc::fire();
        }
        RTC_ClearITPendingBit(RTC_IT_SEC);
        RTC_WaitForLastTask();
        // update time
    }
}

} // namespace rtc
