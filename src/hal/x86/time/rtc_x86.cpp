#include "hal/time/rtc.hpp"

#include <chrono>
#include <cstdio>
#include <ctime>
#include <functional>
#include <memory>
#include <thread>

#include "hal/core/backupRegisters.hpp"

namespace hal
{
namespace time
{

static time_t currentTime;
static bool kill = false;
static std::unique_ptr<std::thread> rtcSecondsInterruptThread;

static bool wasInitialized = false;


Rtc::~Rtc()
{
    kill = true;
    rtcSecondsInterruptThread->join();
}

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
    initSecondsInterrupt();
}

void Rtc::initNvic()
{
}

void Rtc::initSecondsInterrupt()
{
    rtcSecondsInterruptThread.reset(new std::thread([this]() {
        this->logger_.info() << "Started seconds interrupt";

        while (!kill)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (this->secondsHandler_)
            {
                this->secondsHandler_();
            }
        }
    }));
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
    currentTime = timeSinceEpoch;
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
    currentTime = std::time(nullptr);
    return currentTime;
}

std::function<void()>& Rtc::getSecondsHandler()
{
    return secondsHandler_;
}

} // namespace time
} // namespace hal
