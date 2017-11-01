#include "hal/time/sleep.hpp"

#include <stm32f10x.h>

#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

volatile u64 ticks;

void sleep(u32 seconds)
{
    msleep(100 * seconds);
}

void msleep(u64 milliseconds)
{
    u64 prev = Time::getTicks();
    while (Time::getTicks() < prev + milliseconds)
    {
    }
}

} // namespace time
} // namespace hal
