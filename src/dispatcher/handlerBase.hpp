#pragma once

#include "dispatcher/IHandler.hpp"
#include "memoryHelpers.hpp"

namespace handler
{
class HandlerBase : public IHandler
{
  public:
    HandlerBase(char *name);
    char *getName();
  private:
    std::unique_ptr<char, Deleter> name_; 
};
} // namespace handler
 