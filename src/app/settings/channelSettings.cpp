#include "app/settings/channelSettings.hpp"

namespace app
{
namespace settings
{

u8 ChannelSettings::power() const
{
    return power_;
}

u8& ChannelSettings::power()
{
    return power_;
}

void ChannelSettings::power(u8 power)
{
    power_ = power;
}

void ChannelSettings::time(const TimeEventSettings& timeEventSettings)
{
    time_ = timeEventSettings;
}

const TimeEventSettings& ChannelSettings::time() const
{
    return time_;
}

TimeEventSettings& ChannelSettings::time()
{
    return time_;
}

void ChannelSettings::setTime(u8 hour, u8 minute, u8 second, std::time_t length)
{
    time_.hour(hour);
    time_.minute(minute);
    time_.second(second);
    time_.length(length);
}


std::size_t ChannelSettings::fastLength() const
{
    return fastLength_;
}

void ChannelSettings::fastLength(std::size_t length)
{
    fastLength_ = length;
}

} // namespace settings
} // namespace app
