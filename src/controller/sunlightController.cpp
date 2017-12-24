#include "controller/sunlightController.hpp"

#include <iostream>

namespace controller
{

SunlightController::SunlightController(app::Context& context)
    : logger_("SunlightController"),
      state_(State::Finished),
      context_(context)
{
}

SunlightController::State SunlightController::state() const
{
    return state_;
}

void SunlightController::updateState(std::time_t currentTime)
{
    const std::time_t sunsetStart = getSunsetStartTime();
    if (currentTime >= sunsetStart && currentTime < sunsetStart + context_.sunsetSettings().length())
    {
        if (state_ != State::Sunset)
        {
            logger_.info() << "It's sunset time";
            currentPower_ = context_.currentChannelsSettings().masterPower();

            state_ = State::Sunset;
        }

        return;
    }

    const std::time_t sunriseStart = getSunriseStartTime();

    if (currentTime >= sunriseStart && currentTime < sunriseStart + context_.sunriseSettings().length())
    {
        if (state_ != State::Sunrise)
        {
            logger_.info() << "It's sunrise time";
            currentPower_ = context_.currentChannelsSettings().masterPower();
            state_        = State::Sunrise;
        }
        return;
    }
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
            const int timeToEnd = getSunsetStartTime() + context_.sunsetSettings().length() - currentTime;

            if (timeToEnd <= 0)
            {
                logger_.info() << "Set power to: " << context_.nightChannelsSettings().masterPower()
                               << " and finish.";

                context_.currentChannelsSettings().masterPower(
                    context_.nightChannelsSettings().masterPower());
                state_ = State::Finished;
                return;
            }

            const u8 leftPower = context_.currentChannelsSettings().masterPower() - context_.nightChannelsSettings().masterPower();
            const float step   = static_cast<const float>(leftPower) / timeToEnd;
            if (std::abs(currentPower_ - context_.currentChannelsSettings().masterPower()) > 1)
            {
                currentPower_ = context_.currentChannelsSettings().masterPower();
            }

            currentPower_ -= step;
            const u8 newPower = static_cast<u8>(currentPower_);

            if (newPower != context_.currentChannelsSettings().masterPower())
            {
                logger_.info() << "Set power to: " << newPower;
                context_.currentChannelsSettings().masterPower(newPower);
            }
        }
        break;

        case State::Sunrise:
        {
            const int timeToEnd = getSunriseStartTime() + context_.sunriseSettings().length() - currentTime;

            if (timeToEnd <= 0)
            {
                logger_.info() << "Set power to: " << context_.dayChannelsSettings().masterPower()
                               << " and finish.";

                context_.currentChannelsSettings().masterPower(
                    context_.dayChannelsSettings().masterPower());
                state_ = State::Finished;
                return;
            }

            const u8 leftPower = context_.dayChannelsSettings().masterPower() - context_.currentChannelsSettings().masterPower(); // TODO: get
            const float step   = static_cast<const float>(leftPower) / timeToEnd;
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
        break;

        case State::FastSunset:
        {
        }
        break;

        case State::FastSunrise:
        {
        }
        break;
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
