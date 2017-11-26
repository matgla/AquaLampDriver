#include "hal/core/core.hpp"

#include <stm32f10x.h>

#include "hal/utils/assert.hpp"

extern uint32_t SystemCoreClock;

namespace hal
{
namespace core
{

void Core::initializeClocks()
{
    // systick interrupt at 1 ms
    if (SysTick_Config(SystemCoreClock / 1000) != 0)
    {
        HAL_ASSERT_MSG(false, "Systick initialization failed");
    }
}


} // namespace core
} // namespace hal