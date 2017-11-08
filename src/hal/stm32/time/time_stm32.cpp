#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

volatile u64 Time::ticks_(0);

u64 Time::getTicks()
{
    return ticks_;
}

u64 Time::milliseconds()
{
    return ticks_;
}

void Time::incrementTicks()
{
    ++ticks_;
}

void Time::setTicks(u64 ticks)
{
    ticks_ = ticks;
}

} // namespace time
} // namespace hal


extern "C" {
void SysTick_Handler();
}

void SysTick_Handler()
{
    hal::time::Time::incrementTicks();
}