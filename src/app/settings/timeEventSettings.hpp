#pragma once

#include "utils/constants.hpp"
#include "utils/types.hpp"

namespace app
{
namespace settings
{

struct TimeEventSettings
{
    void hour(u8 hour);
    u8 hour() const;
    u8& hour();

    void minute(u8 minute);
    u8 minute() const;
    u8& minute();

    void second(u8 second);
    u8 second() const;
    u8& second();

    void length(std::size_t length);
    std::size_t length() const;
    std::size_t& length();

    void set(u8 hour, u8 minute, u8 second);

private:
    u8 hour_;
    u8 minute_;
    u8 second_;
    size_t length_;
};
static_assert(std::is_pod<TimeEventSettings>::value, "ChannelsSettings must be POD type");


} // namespace settings
} // namespace app
