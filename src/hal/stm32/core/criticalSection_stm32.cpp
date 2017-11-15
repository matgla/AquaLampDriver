#include "hal/core/criticalSection.hpp"

#include <stm32f10x.h>

namespace hal
{
namespace core
{

void startCriticalSection()
{
    __disable_irq();
}

void stopCriticalSection()
{
    __enable_irq();
}

} // namespace core
} // namespace hal