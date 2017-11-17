#include "bsp/onewire.hpp"

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#include "bsp/stm32f1_common/helpers.hpp"

namespace bsp
{

template <>
OneWire<OneWires::OneWire1>::OneWire()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    Helper::configureGpio(GPIOB, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire1>::setAsInput()
{
    Helper::configureGpio(GPIOB, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire1>::setAsOutput()
{
    Helper::configureGpio(GPIOB, GPIO_Pin_10, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
BusState OneWire<OneWires::OneWire1>::getState()
{
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
    {
        return BusState::High;
    }
    return BusState::Low;
}

template <>
void OneWire<OneWires::OneWire1>::setState(BusState state)
{
    if (state == BusState::High)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_10);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_10);
    }
}

} // namespace bsp