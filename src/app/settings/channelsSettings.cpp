#include "app/settings/channelsSettings.hpp"


namespace app
{
namespace settings
{

u8 ChannelsSettings::masterPower() const
{
    return masterPower_;
}

void ChannelsSettings::masterPower(u8 power)
{
    masterPower_ = power;
}

gsl::span<u8> ChannelsSettings::powers()
{
    return gsl::span<u8>{channelPowers_};
}

} // namespace settings
} // namespace app
