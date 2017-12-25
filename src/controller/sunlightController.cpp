#include "controller/sunlightController.hpp"

#include <iostream>

namespace controller
{

SunlightController::SunlightController(app::Context& context)
    : logger_("SunlightController"),
      state_(State::Finished),
      context_(context),
      channelController_(context.currentChannelsSettings().masterPower())
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
    if (currentTime >= sunsetStart && currentTime < sunsetStart + context_.sunsetSettings().length())
    {
        if (state_ != State::Sunset)
        {
            logger_.info() << "It's sunset time";
            std::time_t startTime = getSeconds(context_.sunsetSettings().hour(), context_.sunsetSettings().minute(),
                                               context_.sunsetSettings().second());
            state_                = State::Sunset;
            channelController_.start(startTime, context_.sunriseSettings().length(), context_.dayChannelsSettings().masterPower());
        }

        return;
    }

    const std::time_t sunriseStart = getSunriseStartTime();

    if (currentTime >= sunriseStart && currentTime < sunriseStart + context_.sunriseSettings().length())
    {
        if (state_ != State::Sunrise)
        {
            logger_.info() << "It's sunrise time";
            std::time_t startTime = getSeconds(context_.sunriseSettings().hour(), context_.sunriseSettings().minute(),
                                               context_.sunriseSettings().second());
            state_                = State::Sunrise;
            channelController_.start(startTime, context_.sunriseSettings().length(),
                                     context_.dayChannelsSettings().masterPower());
        }
        return;
    }
}

void SunlightController::fastSunrise(std::time_t startTime)
{
    logger_.info() << "Performing fast sunrise";
    state_ = State::FastSunrise;
    channelController_.start(startTime, context_.fastSunriseLength(),
                             context_.dayChannelsSettings().masterPower());
}

void SunlightController::fastSunset(std::time_t startTime)
{
    logger_.info() << "Performing fast sunset";
    state_ = State::FastSunset;
    channelController_.start(startTime, context_.fastSunsetLength(),
                             context_.nightChannelsSettings().masterPower());
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
            channelController_.update(context_.sunsetSettings().length(),
                                      context_.nightChannelsSettings().masterPower());
        }
        break;

        case State::Sunrise:
        {
            channelController_.update(context_.sunriseSettings().length(),
                                      context_.dayChannelsSettings().masterPower());
        }
        break;

        case State::FastSunset:
        {
            channelController_.update(context_.fastSunsetLength(),
                                      context_.nightChannelsSettings().masterPower());
        }
        break;

        case State::FastSunrise:
        {
            channelController_.update(context_.fastSunriseLength(),
                                      context_.dayChannelsSettings().masterPower());
        }
        break;
        case State::FastCorrection:
        {
        }
        break;
    }

    auto state = channelController_.run(currentTime);

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
    state_         = State::FastCorrection;
    setPointValue_ = setPointValue;
    startTime_     = startTime;
    currentPower_  = context_.currentChannelsSettings().masterPower();
    processLength_ = 100;
    channelController_.start(startTime, 100, setPointValue);
}

void SunlightController::process(std::time_t currentTime)
{
    const int timeToEnd = startTime_ + processLength_ - currentTime;
    if (timeToEnd <= 0)
    {
        int error = std::abs(setPointValue_ - context_.currentChannelsSettings().masterPower());
        if (error == 0)
        {
            logger_.info() << "Fast sunrise finished";
            state_ = State::Finished;
            return;
        }

        if (error < 5)
        {
            logger_.info() << "Corrected, sunrise finished";
            state_ = State::Finished;
            return;
        }

        if (error >= 5)
        {
            logger_.info() << "Error to high, performing fast correction...";
            fastCorrection(currentTime, setPointValue_);
            return;
        }
    }

    const int leftPower = setPointValue_ - context_.currentChannelsSettings().masterPower(); // TODO: get
    logger_.info() << "Power left: " << leftPower;
    const float step = static_cast<const float>(leftPower) / timeToEnd;
    if (std::abs(currentPower_ - context_.currentChannelsSettings().masterPower()) > 1)
    {
        currentPower_ = context_.currentChannelsSettings().masterPower();
    }

    currentPower_ += step;
    const u8 newPower = static_cast<u8>(currentPower_);

    if (newPower != context_.currentChannelsSettings().masterPower())
    {
        logger_.info() << "Set power to: " << newPower;
        context_.currentChannelsSettings().masterPower(newPower);
    }
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
    return getSeconds(context_.sunriseSettings().hour(), context_.sunriseSettings().minute(),
                      context_.sunriseSettings().second());
}

std::time_t SunlightController::getSunsetStartTime() const
{
    return getSeconds(context_.sunsetSettings().hour(), context_.sunsetSettings().minute(),
                      context_.sunsetSettings().second());
}

} // namespace controller
