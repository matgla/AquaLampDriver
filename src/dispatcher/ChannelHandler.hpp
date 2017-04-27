#pragma once

#include "dispatcher/handlerBase.hpp"

namespace handler
{
class ChannelHandler : public HandlerBase
{
  public:
    ChannelHandler(char *name);
    void handle(char *cmd, char *arg) override;
    bool accept(char *cmd, char *arg) override;
};
} // namespace handler
 