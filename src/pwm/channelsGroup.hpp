#pragma once

#include "pwmChannel.hpp"
#include "memoryHelpers.hpp"
#include "types.hpp"
#include "logger.hpp"

#define NR_OF_PWM_CHANNELS 12

namespace pwm
{

class ChannelsGroup
{
  public:
    ChannelsGroup();
    void configureChannel(u8 channelNr);
    void configureAllChannels();
    bool setChannelPulse(u8 channelNr, u8 value);

  private:
    std::unique_ptr<Channel> channels_[NR_OF_PWM_CHANNELS];
    Logger logger_;
};

} // namespace pwm