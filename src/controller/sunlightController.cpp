#include "controller/sunlightController.hpp"

namespace controller
{

SunlightController::SunlightController()
    : state_(SunlightController::State::Off)
{
}

SunlightController::SunlightController(const std::time_t sunriseStartTime,
                                       const std::time_t sunriseLength,
                                       const std::time_t sunshineStartTime,
                                       const std::time_t sunshineLength)
    : sunriseStartTime_(sunriseStartTime),
      sunriseLength_(sunriseLength),
      sunshineStartTime_(sunshineStartTime),
      sunshineLength_(sunshineLength)
{
}

const SunlightController::State SunlightController::state() const
{
    return state_;
}

void SunlightController::run(std::time_t currentTime)
{
    switch (state_)
    {
        case State::Off:
        {
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

void SunlightController::setSunriseLength(const std::time_t sunshineLength)
{
    sunshineLength_ = sunshineLength;
}


} // namespace controller
