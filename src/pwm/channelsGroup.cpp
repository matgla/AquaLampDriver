#include "pwm/channelsGroup.hpp"

#include "hal/core/core.hpp"

namespace pwm
{
ChannelsGroup::ChannelsGroup()
    : logger_("ChannelsGroup\0")
{
}

void ChannelsGroup::configureChannel(u8 channelNr)
{
    HAL_ASSERT_MSG(channelNr >= 0 && channelNr <= 13, "Wrong channel for configure");
    channels_[channelNr] = pwm::makeChannel(channelNr);
}

void ChannelsGroup::configureAllChannels()
{
    for (int i = 0; i < NR_OF_PWM_CHANNELS; ++i)
    {
        channels_[i] = pwm::makeChannel(i);
    }
}

bool ChannelsGroup::setChannelPulse(u8 channelNr, u8 value)
{
    if (channelNr < 0 || channelNr > 14)
    {
        logger_.error() << "Wrong channel nr: " << channelNr << " 0 <= n < 12\n";
        return false;
    }
    if (value < 0 || value > 100)
    {
        logger_.error() << "Wrong value: " << channelNr << " (0 <= v <= 100)\n";
        return false;
    }

    if (nullptr == channels_[channelNr])
    {
        logger_.error() << "Channel " << channelNr << " isn't configured\n";
        return false;
    }
    channels_[channelNr]->setPulse(value);
    return true;
}

u8 ChannelsGroup::getChannelPulse(u8 channelNr)
{
    return channels_[channelNr]->getPulse();
}

} // namespace pwm
