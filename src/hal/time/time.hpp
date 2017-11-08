#pragma once

#include "utils/types.hpp"

namespace hal
{
namespace time
{

class Time
{
public:
    static u64 getTicks();
    static void incrementTicks();
    static void setTicks(u64 ticks);
    static u64 milliseconds();

private:
    static volatile u64 ticks_;
};

} // namespace time
} // namespace hal
