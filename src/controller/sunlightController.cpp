#include "controller/sunlightController.hpp"

namespace controller
{

SunlightController::SunlightController()
    : logger_("SunlightController"),
      state_(SunlightController::State::Off)
{
}

const SunlightController::State SunlightController::state() const
{
    return state_;
}

void SunlightController::run(std::time_t currentTime)
{
    logger_.info() << "run: " << currentTime;

    switch (state_)
    {
        case State::Off:
        {
            logger_.info() << "State Off entry, time: " << currentTime;
            if (currentTime >= sunshineStartTime_)
            {
                logger_.info() << "Go from off to sunshine";
                state_ = State::Sunshine;
                return;
            }

            if (currentTime >= sunriseStartTime_)
            {
                logger_.info() << "Go from off to sunrise";
                state_ = State::Sunrise;
                return;
            }
        }
        break;
        case State::Sunrise:
        {
            
        }
        break;
    }
}

void SunlightController::setSunriseStartTime(const u8 hour, const u8 minute, const u8 second)
{
    sunriseStartHour_ = hour;
    sunriseStartMinute_ = minute;
    sunriseStartSecond_ = second;
}

void SunlightController::setSunshineStartTime(const u8 hour, const u8 minute, const u8 second)
{
    sunshineStartHour_ = hour;
    sunshineStartMinute_ = minute;
    sunshineStartSecond_ = second;
}

void SunlightController::setSunriseLength(const std::time_t sunriseLength)
{
    sunriseLength_ = sunriseLength;
}

void SunlightController::setSunshineLength(const std::time_t sunshineLength)
{
    sunshineLength_ = sunshineLength;
}

std::time_t SunlightController::getSeconds(int hour, int minute, int second)
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeData       = localtime(&currentTime);
    timeData->tm_hour       = hour;
    timeData->tm_min        = minute;
    timeData->tm_sec        = second;

    return std::mktime(timeData);
}

} // namespace controller
