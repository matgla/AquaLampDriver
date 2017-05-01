#pragma once

#include "dispatcher/IHandler.hpp"
#include "memoryHelpers.hpp"
#include "logger.hpp"

namespace handler
{
class HandlerBase : public IHandler
{
  public:
    HandlerBase(char *name);
    char *getName();

  protected:
    std::unique_ptr<char, Deleter> name_;
    Logger logger_;
};
} // namespace handler
