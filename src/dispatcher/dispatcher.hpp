#pragma once

#include "logger/logger.hpp"

#include <functional>
#include <vector>

#include "dispatcher/IHandler.hpp"

namespace dispatcher
{
class Dispatcher
{
  public:
    Dispatcher();
    bool handle(char* msg);
    bool registerHandler(handler::IHandlerPtr handler);

  private:
    void dispatch(char* cmd, char* arg);
    logger::Logger logger_;
    std::vector<handler::IHandlerPtr> handlers_;
};
} // namespace handler
