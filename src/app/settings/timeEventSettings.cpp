#include "app/settings/timeEventSettings.hpp"

namespace app
{
namespace settings
{

void TimeEventSettings::hour(u8 hour)
{
    hour_ = hour;
}

u8 TimeEventSettings::hour() const
{
    return hour_;
}

void TimeEventSettings::minute(u8 minute)
{
    minute_ = minute;
}

u8 TimeEventSettings::minute() const
{
    return minute_;
}

void TimeEventSettings::second(u8 second)
{
    second_ = second;
}

u8 TimeEventSettings::second() const
{
    return second_;
}

void TimeEventSettings::length(std::size_t length)
{
    length_ = length;
}

std::size_t TimeEventSettings::length() const
{
    return length_;
}

void TimeEventSettings::set(u8 hour, u8 minute, u8 second)
{
    hour_   = hour;
    minute_ = minute;
    second_ = second;
}

} // namespace settings
} // namespace app
