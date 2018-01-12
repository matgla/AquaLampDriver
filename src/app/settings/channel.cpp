#include "app/settings/channel.hpp"

namespace app
{
namespace settings
{

u8 Channel::dayPower() const
{
    return dayPower_;
}

u8& Channel::dayPower()
{
    return dayPower_;
}

void Channel::dayPower(u8 power)
{
    dayPower_ = power;
}

u8 Channel::nightPower() const
{
    return nightPower_;
}

u8& Channel::nightPower()
{
    return nightPower_;
}

void Channel::nightPower(u8 power)
{
    nightPower_ = power;
}

u8 Channel::currentPower() const
{
    return currentPower_;
}

u8& Channel::currentPower()
{
    return currentPower_;
}

void Channel::currentPower(u8 power)
{
    currentPower_ = power;
}

void Channel::setSunriseTime(u8 hour, u8 minute, u8 second, std::time_t length)
{
    sunriseTime_.hour(hour);
    sunriseTime_.minute(minute);
    sunriseTime_.second(second);
    sunriseTime_.length(length);
}

void Channel::setSunsetTime(u8 hour, u8 minute, u8 second, std::time_t length)
{
    sunsetTime_.hour(hour);
    sunsetTime_.minute(minute);
    sunsetTime_.second(second);
    sunsetTime_.length(length);
}

const TimeEventSettings& Channel::getSunriseTime() const
{
    return sunriseTime_;    
}

TimeEventSettings& Channel::getSunriseTime()
{
    return sunriseTime_;
}

const TimeEventSettings& Channel::getSunsetTime() const
{
    return sunsetTime_;
}

TimeEventSettings& Channel::getSunsetTime()
{
    return sunsetTime_;
}

std::size_t Channel::fastOperationLength() const
{
    return fastOperationLength_;
}

std::size_t& Channel::fastOperationLength()
{
    return fastOperationLength_;
}
    
void Channel::fastOperationLength(std::size_t length)
{
    fastOperationLength_ = length;    
}
    

} // namespace settings
} // namespace app
