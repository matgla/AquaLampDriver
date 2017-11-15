#include "hal/time/rtc.hpp"

#include <cstdio>
#include <ctime>
#include <functional>

#include "stm32f10x_conf.h"

#include "hal/core/backupRegisters.hpp"

namespace hal
{
namespace time
{
static bool wasInitialized = false;

Rtc& Rtc::get()
{
    static Rtc rtc;
    hal::time::wasInitialized = true;
    return rtc;
}

bool Rtc::wasInitialized()
{
    return hal::time::wasInitialized;
}

Rtc::Rtc()
    : timerCallback_(nullptr),
      secondsHandler_(nullptr),
      alarmTime_(0),
      alarmEnabled_(0),
      logger_("Rtc")
{
    if (hal::core::BackupRegisters::get().isFirstStartup())
    {
        init();
        logger_.info() << "Performed full initialization";
    }
    else
    {
        initSecondsInterrupt();
        initNvic();
        logger_.info() << "Performed normal initialization";
    }
}

Rtc::~Rtc()
{
}

void Rtc::stop()
{
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

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);

    initSecondsInterrupt();

    RTC_WaitForLastTask();
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
    RTC_WaitForLastTask();
    initNvic();
}

void Rtc::initNvic()
{
    NVIC_InitTypeDef nvic;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    nvic.NVIC_IRQChannel = RTC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

void Rtc::initSecondsInterrupt()
{
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
}

void Rtc::setTime(u32 hours, u32 minutes, u32 seconds)
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* t = localtime(&currentTime);
    t->tm_hour = hours;
    t->tm_min = minutes;
    t->tm_sec = seconds;
    time_t timeSinceEpoch = mktime(t);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_WaitForLastTask();

    RTC_SetCounter(timeSinceEpoch);
    RTC_WaitForLastTask();
}

void Rtc::setDate(u32 day, u32 month, u32 year)
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* t = localtime(&currentTime);
    t->tm_year = year - 1900;
    t->tm_mon = month - 1;
    t->tm_mday = day;
    time_t timeSinceEpoch = mktime(t);
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

std::function<void()>& Rtc::getSecondsHandler()
{
    return secondsHandler_;
}

extern "C" {
void RTC_IRQHandler();
}

void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
    {
        if (Rtc::get().getSecondsHandler())
        {
            Rtc::get().getSecondsHandler()();
        }
        if (RTC_GetCounter() >= Rtc::get().alarmTime())
        {
            Rtc::get().fire();
        }
        RTC_ClearITPendingBit(RTC_IT_SEC);
        RTC_WaitForLastTask();
    }
}
} // namespace time
} // namespace hal
