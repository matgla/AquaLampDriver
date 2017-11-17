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

volatile bool initialized = false;
volatile u32 cyclesFor1MicroSecond = 0;

void usleep(u32 microseconds)
{
    if (!initialized)
    {
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq(&RCC_Clocks);
        cyclesFor1MicroSecond = RCC_Clocks.HCLK_Frequency / 4000000;
    }
    microseconds = microseconds * cyclesFor1MicroSecond - 10;
    while (microseconds--)
    {
    }
}

} // namespace time
} // namespace hal
