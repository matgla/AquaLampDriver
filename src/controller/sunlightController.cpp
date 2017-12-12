#include "controller/sunlightController.hpp"

namespace controller
{

SunlightController::SunlightController()
    : logger_("SunlightController"),
      state_(SunlightController::State::Off)
{
}

SunlightController::SunlightController(const std::time_t sunriseStartTime,
                                       const std::time_t sunriseLength,
                                       const std::time_t sunshineStartTime,
                                       const std::time_t sunshineLength)
    : sunriseStartTime_(sunriseStartTime),
      sunriseLength_(sunriseLength),
      sunshineStartTime_(sunshineStartTime),
      sunshineLength_(sunshineLength),
      logger_("SunlightController"),
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
    }
}

void SunlightController::setSunriseStartTime(const std::time_t sunriseStartTime)
{
    sunriseStartTime_ = sunriseStartTime;
}

void SunlightController::setSunshineStartTime(const std::time_t sunshineStartTime)
{
    sunshineStartTime_ = sunshineStartTime;
}

void SunlightController::setSunriseLength(const std::time_t sunriseLength)
{
    sunriseLength_ = sunriseLength;
}

void SunlightController::setSunshineLength(const std::time_t sunshineLength)
{
    sunshineLength_ = sunshineLength;
}


} // namespace controller
