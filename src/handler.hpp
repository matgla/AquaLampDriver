#pragma once

#include "logger.hpp"

namespace handler
{
class Handler
{
  public:
    Handler();
    bool handle(char *msg);

  private:
    Logger logger_;
};
} // namespace handler