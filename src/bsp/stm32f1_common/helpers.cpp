#include "bsp/helpers.hpp"

namespace bsp
{

void Helpers::configureGpio(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = pin;
    gpio.GPIO_Mode = mode;
    gpio.GPIO_Speed = speed;
    GPIO_Init(port, &gpio);
}

} // namespace bsp