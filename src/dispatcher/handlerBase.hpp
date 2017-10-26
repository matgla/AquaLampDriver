#pragma once

#include "dispatcher/IHandler.hpp"
#include "logger/logger.hpp"
#include "memoryHelpers.hpp"

namespace handler
{
class HandlerBase : public IHandler
{
  public:
    HandlerBase(char* name);
    char* getName();

  protected:
    std::unique_ptr<char, Deleter> name_;
    logger::Logger logger_;
};
} // namespace handler
