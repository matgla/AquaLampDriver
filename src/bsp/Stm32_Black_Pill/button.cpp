#include "bsp/button.hpp"

#include "bsp/stm32f1_common/helpers.hpp"

namespace bsp
{


template <>
Button<Buttons::Left>::Button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    initializeGPIO(GPIOA, GPIO_Pin_4, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Right>::Button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
    initializeGPIO(GPIOA, GPIO_Pin_5, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Up>::Button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    initializeGPIO(GPIOB, GPIO_Pin_15, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Down>::Button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    initializeGPIO(GPIOA, GPIO_Pin_12, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Back>::Button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    initializeGPIO(GPIOB, GPIO_Pin_13, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Select>::Button()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    initializeGPIO(GPIOB, GPIO_Pin_14, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
bool Button<Buttons::Left>::isPinPressed()
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
}

template <>
bool Button<Buttons::Right>::isPinPressed()
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
}

template <>
bool Button<Buttons::Up>::isPinPressed()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
}

template <>
bool Button<Buttons::Down>::isPinPressed()
{
    return 0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
}

template <>
bool Button<Buttons::Back>::isPinPressed()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}

template <>
bool Button<Buttons::Select>::isPinPressed()
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
}

template class Button<Buttons::Right>;
template class Button<Buttons::Left>;

} // namespace bsp