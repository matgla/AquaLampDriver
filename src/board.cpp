#include "board.hpp"

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "hal/core/core.hpp"
#include "rtc/rtc.hpp"

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
    
}

template <Buttons button>
bool Button<button>::isPinPressed()
{
    static_assert(sizeof(button), "Default constructor can't be used");
    return false;
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
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

template <>
void Led<Leds::Led1>::off()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void CoreInit()
{
    SystemInit();
}

Board::Board()
    : registers(hal::core::BackupRegisters::get()),
      logger_("Board")
{
    hal::core::Core::initializeClocks();
    logger_.info() << "Initialized";
}