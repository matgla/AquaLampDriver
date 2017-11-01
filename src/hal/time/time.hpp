#pragma once

#include "utils/types.hpp"

namespace hal
{
namespace time
{

class Time
{
  public:
    static volatile u64 getTicks();
    static volatile void incrementTicks();
    static volatile void setTicks(u64 ticks);
    static volatile u64 milliseconds();

  private:
    static volatile u64 ticks_;
};

} // namespace time
} // namespace hal
