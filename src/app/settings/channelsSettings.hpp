#pragma once

#include <type_traits>

#include <gsl/span>

#include "app/settings/channelSettings.hpp"
#include "app/settings/timeEventSettings.hpp"
#include "utils/constants.hpp"
#include "utils/types.hpp"

namespace app
{
namespace settings
{

struct ChannelsSettings
{
    ChannelSettings& masterDay();
    const ChannelSettings& masterDay() const;

    ChannelSettings& masterNight();
    const ChannelSettings& masterNight() const;

    gsl::span<ChannelSettings> day();
    gsl::span<const ChannelSettings> day() const;

    gsl::span<ChannelSettings> night();
    gsl::span<const ChannelSettings> night() const;

private:
    ChannelSettings masterDaySettings_;
    ChannelSettings masterNightSettings_;
    ChannelSettings channelsDaySettings_[utils::NUMBER_OF_PWM_CHANNELS];
    ChannelSettings channelsNightSettings_[utils::NUMBER_OF_PWM_CHANNELS];
};
static_assert(std::is_pod<ChannelsSettings>::value, "ChannelsSettings must be POD type");

} // namespace settings
} // namespace app
