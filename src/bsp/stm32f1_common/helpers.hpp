#pragma once

#include <cstdint>

#include <stm32f10x_gpio.h>

namespace bsp
{

struct Helper
{
    static void configureGpio(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);
};

} // namespace bsp