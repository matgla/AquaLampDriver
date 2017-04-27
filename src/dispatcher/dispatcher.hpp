#pragma once

#include "logger.hpp"

#include <functional>
#include <vector>

#include "IHandler.hpp"

namespace dispatcher
{
class Dispatcher
{
  public:
    Dispatcher();
    bool handle(char *msg);
    bool registerHandler(handler::IHandlerPtr handler);

  private:
    void dispatch(char *cmd, char *arg);
    Logger logger_;
    std::vector<handler::IHandlerPtr> handlers_;
};
} // namespace handler