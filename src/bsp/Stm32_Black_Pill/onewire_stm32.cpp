#include "bsp/onewire.hpp"

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#include "bsp/stm32f1_common/helpers.hpp"

#define ONE_WIRE_PORT GPIOB
#define ONE_WIRE_PIN GPIO_Pin_14
#define RCC_ONE_WIRE RCC_APB2Periph_GPIOB

namespace bsp
{

template <>
OneWire<OneWires::OneWire1>::OneWire()
{
    RCC_APB2PeriphClockCmd(RCC_ONE_WIRE, ENABLE);
    Helper::configureGpio(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire1>::setAsInput()
{
    Helper::configureGpio(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
void OneWire<OneWires::OneWire1>::setAsOutput()
{
    Helper::configureGpio(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
BusState OneWire<OneWires::OneWire1>::getState()
{
    if (GPIO_ReadInputDataBit(ONE_WIRE_PORT, ONE_WIRE_PIN))
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
        GPIO_SetBits(ONE_WIRE_PORT, ONE_WIRE_PIN);
    }
    else
    {
        GPIO_ResetBits(ONE_WIRE_PORT, ONE_WIRE_PIN);
    }
}

} // namespace bsp