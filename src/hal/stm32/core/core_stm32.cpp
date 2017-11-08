#include "hal/core/core.hpp"

#include <cassert>

#include <stm32f10x.h>

#include "logger/logger.hpp"

extern uint32_t SystemCoreClock;

namespace hal
{
namespace core
{

namespace
{
logger::Logger logger("core");
}

void Core::initializeClocks()
{
    // systick interrupt at 1 ms
    if (SysTick_Config(SystemCoreClock / 1000000 * 1000) != 0)
    {
        logger.error() << "System clock intialization failed";
        assert(false);
    }
}


} // namespace core
} // namespace hal