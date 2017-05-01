#pragma once

#include "dispatcher/handlerBase.hpp"
#include "pwm/channelsGroup.hpp"

namespace handler
{
class RtcHandler : public HandlerBase
{
  public:
    RtcHandler(char *name);
    void handle(char *cmd, char *arg) override;
    bool accept(char *cmd, char *arg) override;
};
} // namespace handler