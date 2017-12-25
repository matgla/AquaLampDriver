#include "app/settings/channelsSettings.hpp"


namespace app
{
namespace settings
{

ChannelSettings& ChannelsSettings::masterDay()
{
    return masterDaySettings_;
}

// const ChannelSettings& ChannelsSettings::masterDay() const
// {
//     return masterDaySettings_;
// }

ChannelSettings& ChannelsSettings::masterNight()
{
    return masterNightSettings_;
}

const ChannelSettings& ChannelsSettings::masterNight() const
{
    return masterNightSettings_;
}

gsl::span<ChannelSettings> ChannelsSettings::day()
{
    return gsl::span<ChannelSettings>{channelsDaySettings_};
}

gsl::span<const ChannelSettings> ChannelsSettings::day() const
{
    return gsl::span<const ChannelSettings>{channelsDaySettings_};
}

gsl::span<ChannelSettings> ChannelsSettings::night()
{
    return gsl::span<ChannelSettings>{channelsNightSettings_};
}

gsl::span<const ChannelSettings> ChannelsSettings::night() const
{
    return gsl::span<const ChannelSettings>{channelsNightSettings_};
}

} // namespace settings
} // namespace app
