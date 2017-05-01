#pragma once

#include "dispatcher/handlerBase.hpp"
#include "pwm/channelsGroup.hpp"

namespace handler
{
class ChannelHandler : public HandlerBase
{
public:
  ChannelHandler(char *name, pwm::ChannelsGroup &channelsGroup);
  void handle(char *cmd, char *arg) override;
  bool accept(char *cmd, char *arg) override;

private:
  pwm::ChannelsGroup &channelsGroup_;
};
} // namespace handler
