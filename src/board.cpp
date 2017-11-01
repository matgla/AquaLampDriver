#include "board.hpp"

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

namespace
{

void initializeGPIO(GPIO_TypeDef* port, u16 pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = pin;
    gpio.GPIO_Mode = mode;
    gpio.GPIO_Speed = speed;
    GPIO_Init(port, &gpio);
}
}

template <Buttons button>
Button<button>::Button()
{
    static_assert(sizeof(button), "Default constructor can't be used");
}

template <Buttons button>
bool Button<button>::isPinPressed()
{
    static_assert(sizeof(button), "Default constructor can't be used");
    return false;
}

template <>
Button<Buttons::Left>::Button()
{
    initializeGPIO(GPIOA, GPIO_Pin_4, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Right>::Button()
{
    initializeGPIO(GPIOA, GPIO_Pin_5, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Up>::Button()
{
    initializeGPIO(GPIOB, GPIO_Pin_15, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Down>::Button()
{
    initializeGPIO(GPIOA, GPIO_Pin_12, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Back>::Button()
{
    initializeGPIO(GPIOB, GPIO_Pin_13, GPIO_Mode_IPD, GPIO_Speed_50MHz);
}

template <>
Button<Buttons::Select>::Button()
{
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

template <Leds led>
Led<led>::Led()
{
    static_assert(sizeof(led), "Default constructor can't be used");
}

template <Leds led>
void Led<led>::on()
{
    static_assert(sizeof(led), "Default constructor can't be used");
}

template <Leds led>
void Led<led>::off()
{
    static_assert(sizeof(led), "Default constructor can't be used");
}

template <>
Led<Leds::Led1>::Led()
{
    initializeGPIO(GPIOB, GPIO_Pin_12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

template <>
void Led<Leds::Led1>::on()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

template <>
void Led<Leds::Led1>::off()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

Board::Board()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
}