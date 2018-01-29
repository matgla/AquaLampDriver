#include "app/settings/lightChannel.hpp"

namespace app
{
namespace settings
{

u8 LightChannel::dayPower() const
{
    return dayPower_;
}

u8& LightChannel::dayPower()
{
    return dayPower_;
}

void LightChannel::dayPower(u8 power)
{
    dayPower_ = power;
}

u8 LightChannel::nightPower() const
{
    return nightPower_;
}

u8& LightChannel::nightPower()
{
    return nightPower_;
}

void LightChannel::nightPower(u8 power)
{
    nightPower_ = power;
}

u8 LightChannel::currentPower() const
{
    return currentPower_;
}

u8& LightChannel::currentPower()
{
    return currentPower_;
}

void LightChannel::currentPower(u8 power)
{
    currentPower_ = power;
}

void LightChannel::setSunriseTime(u8 hour, u8 minute, u8 second, std::time_t length)
{
    sunriseTime_.hour(hour);
    sunriseTime_.minute(minute);
    sunriseTime_.second(second);
    sunriseTime_.length(length);
}

void LightChannel::setSunsetTime(u8 hour, u8 minute, u8 second, std::time_t length)
{
    sunsetTime_.hour(hour);
    sunsetTime_.minute(minute);
    sunsetTime_.second(second);
    sunsetTime_.length(length);
}

const TimeEventSettings& LightChannel::getSunriseTime() const
{
    return sunriseTime_;
}

TimeEventSettings& LightChannel::getSunriseTime()
{
    return sunriseTime_;
}

const TimeEventSettings& LightChannel::getSunsetTime() const
{
    return sunsetTime_;
}

TimeEventSettings& LightChannel::getSunsetTime()
{
    return sunsetTime_;
}

std::size_t LightChannel::fastOperationLength() const
{
    return fastOperationLength_;
}

std::size_t& LightChannel::fastOperationLength()
{
    return fastOperationLength_;
}

void LightChannel::fastOperationLength(std::size_t length)
{
    fastOperationLength_ = length;
}


} // namespace settings
} // namespace app
