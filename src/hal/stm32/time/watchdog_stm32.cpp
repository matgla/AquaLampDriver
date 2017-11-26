#include "hal/time/watchdog.hpp"

#include <cstdint>

#include <stm32f10x_iwdg.h>

constexpr uint16_t LSI_FREQ = 40000;

namespace hal
{
namespace time
{

void WatchDog::enable(int milliseconds)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_4);

    IWDG_SetReload((LSI_FREQ / 400) * milliseconds);
    IWDG_ReloadCounter();
    IWDG_Enable();
}

void WatchDog::feed()
{
    IWDG_ReloadCounter();
}

} // namespace time
} // namespace hal
