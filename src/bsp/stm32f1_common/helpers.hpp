#pragma once

#include <cstdint>
#include <functional>

#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>

namespace bsp
{

struct Helper
{
    static void configureGpio(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);
    static uint32_t configureTimer(TIM_TypeDef* timer, uint16_t mode, uint16_t frequency);
    static uint8_t setPwmPulse(TIM_TypeDef* timer, std::function<void(TIM_TypeDef*, TIM_OCInitTypeDef*)> ocInit, uint8_t period, uint8_t width);
    static void initPwmClocks(TIM_TypeDef* timer, u32 timerPeriphRcc, u32 gpioRcc);
};

} // namespace bsp