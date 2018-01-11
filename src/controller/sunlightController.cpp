#include "controller/sunlightController.hpp"

#include <iostream>

namespace controller
{

SunlightController::SunlightController(app::Context& context)
    : logger_("SunlightController"),
      state_(State::Finished),
      context_(context),
      masterController_(context.currentMasterPower())
{
}

SunlightController::State SunlightController::state() const
{
    return state_;
}

void SunlightController::updateState(std::time_t currentTime)
{
    if (state_ == State::FastSunrise || state_ == State::FastSunset)
    {
        return;
    }
    const std::time_t sunsetStart = getSunsetStartTime();
    if (currentTime >= sunsetStart && currentTime < sunsetStart + context_.channelsSettings().masterNight().time().length())
    {
        if (state_ != State::Sunset)
        {
            logger_.info() << "It's sunset time";
            std::time_t startTime = getSeconds(context_.channelsSettings().masterNight().time().hour(),
                                               context_.channelsSettings().masterNight().time().minute(),
                                               context_.channelsSettings().masterNight().time().second());
            state_                = State::Sunset;
            masterController_.start(startTime,
                                     context_.channelsSettings().masterNight().time().length(),
                                     context_.channelsSettings().masterNight().power());
        }

        return;
    }

    const std::time_t sunriseStart = getSunriseStartTime();

    if (currentTime >= sunriseStart && currentTime < sunriseStart + context_.channelsSettings().masterDay().time().length())
    {
        if (state_ != State::Sunrise)
        {
            logger_.info() << "It's sunrise time";
            std::time_t startTime = getSeconds(context_.channelsSettings().masterDay().time().hour(),
                                               context_.channelsSettings().masterDay().time().minute(),
                                               context_.channelsSettings().masterDay().time().second());
            state_                = State::Sunrise;
            masterController_.start(startTime, context_.channelsSettings().masterDay().time().length(),
                                     context_.channelsSettings().masterDay().power());
        }
        return;
    }
}

void SunlightController::fastSunrise(std::time_t startTime)
{
    logger_.info() << "Performing fast sunrise";
    state_ = State::FastSunrise;
    masterController_.start(startTime, context_.channelsSettings().masterDay().fastLength(),
                             context_.channelsSettings().masterDay().power());
}

void SunlightController::fastSunset(std::time_t startTime)
{
    logger_.info() << "Performing fast sunset";
    state_ = State::FastSunset;
    masterController_.start(startTime, context_.channelsSettings().masterNight().fastLength(),
                             context_.channelsSettings().masterNight().power());
}

void SunlightController::run(std::time_t currentTime)
{
    updateState(currentTime);
    switch (state_)
    {
        case State::Finished:
        {
        }
        break;

        case State::Sunset:
        {
            masterController_.update(context_.channelsSettings().masterNight().time().length(),
                                      context_.channelsSettings().masterNight().power());
        }
        break;

        case State::Sunrise:
        {
            masterController_.update(context_.channelsSettings().masterDay().time().length(),
                                      context_.channelsSettings().masterDay().power());
        }
        break;

        case State::FastSunset:
        {
            masterController_.update(context_.channelsSettings().masterNight().fastLength(),
                                      context_.channelsSettings().masterNight().power());
        }
        break;

        case State::FastSunrise:
        {
            masterController_.update(context_.channelsSettings().masterDay().fastLength(),
                                      context_.channelsSettings().masterDay().power());
        }
        break;
        case State::FastCorrection:
        {
        }
        break;
    }

    auto state = masterController_.run(currentTime);

    if (state == ChannelController::State::Finished)
    {
        state_ = State::Finished;
    }
    else if (state == ChannelController::State::Correction)
    {
        state_ = State::FastCorrection;
    }
}

void SunlightController::fastCorrection(std::time_t startTime, u8 setPointValue)
{
    state_ = State::FastCorrection;
    // TODO: remove hardcode
    masterController_.start(startTime, 100, setPointValue);
}

void SunlightController::stop()
{
    state_ = State::Finished;
}

std::time_t SunlightController::getSeconds(int hour, int minute, int second) const
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeData       = localtime(&currentTime);
    timeData->tm_hour       = hour;
    timeData->tm_min        = minute;
    timeData->tm_sec        = second;

    return std::mktime(timeData);
}

std::time_t SunlightController::getSunriseStartTime() const
{
    return getSeconds(context_.channelsSettings().masterDay().time().hour(),
                      context_.channelsSettings().masterDay().time().minute(),
                      context_.channelsSettings().masterDay().time().second());
}

std::time_t SunlightController::getSunsetStartTime() const
{
    return getSeconds(context_.channelsSettings().masterNight().time().hour(),
                      context_.channelsSettings().masterNight().time().minute(),
                      context_.channelsSettings().masterNight().time().second());
}

} // namespace controller
