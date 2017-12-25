#pragma once

#include <type_traits>

#include "app/settings/timeEventSettings.hpp"
#include "utils/constants.hpp"
#include "utils/types.hpp"

namespace app
{
namespace settings
{

struct ChannelSettings
{
    u8 power() const;
    u8& power();

    void power(u8 power);

    void time(const TimeEventSettings& timeEventSettings);
    const TimeEventSettings& time() const;
    TimeEventSettings& time();

    void setTime(u8 hour, u8 minute, u8 second, std::time_t length);

    std::size_t fastLength() const;
    void fastLength(std::size_t length);

private:
    u8 power_;
    std::size_t fastLength_;
    TimeEventSettings time_;
};

static_assert(std::is_pod<ChannelSettings>::value, "ChannelSettings must be POD type");

} // namespace settings
} // namespace app
