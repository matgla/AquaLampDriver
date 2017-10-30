#pragma once

#include "logger.hpp"
#include "memoryHelpers.hpp"
#include "pwmChannel.hpp"
#include "types.hpp"

#define NR_OF_PWM_CHANNELS 14

namespace pwm
{

class ChannelsGroup
{
  public:
    ChannelsGroup();
    void configureChannel(u8 channelNr);
    void configureAllChannels();
    bool setChannelPulse(u8 channelNr, u8 value);
    u8 getChannelPulse(u8 channelNr);

  private:
    std::unique_ptr<Channel> channels_[NR_OF_PWM_CHANNELS];
    Logger logger_;
};

} // namespace pwm
