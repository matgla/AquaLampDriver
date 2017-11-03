#include "bsp/led.hpp"

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#include "bsp/stm32f1_common/helpers.hpp"

namespace bsp
{

template <>
Led<Leds::Led1>::Led()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    Helpers::configureGpio(GPIOB, GPIO_Pin_12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
void Led<Leds::Led1>::on()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

template <>
void Led<Leds::Led1>::off()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

} // namespace bsp