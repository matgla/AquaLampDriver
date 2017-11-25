#include "bsp/pwm.hpp"

#include "bsp/stm32f1_common/helpers.hpp"

namespace bsp
{

// template <>
// void Pwm<Channels::Channel1>::Pwm()
// {
//     helper::configureGpio(GPIO_Pin_8)
// }

// template <>
// void Pwm<Channels::Channel1>::setPulse(u8 width)
// {
//     UNUSED(width);
// }

// template class Pwm<Channels::Channel1>;
//     static void configureGpio(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);

template <>
void Pwm<Channels::Channel13>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM4, &TIM_OC3Init, period_, width);
}

template <>
Pwm<Channels::Channel13>::Pwm()
{
    Helper::initPwmClocks(TIM4, RCC_APB1Periph_TIM4, RCC_APB2Periph_GPIOB);
    Helper::configureGpio(GPIOB, GPIO_Pin_8, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
    period_ = Helper::configureTimer(TIM4, TIM_CounterMode_Up, 10000); // 10 KHz
    setPulse(0);
}

template <>
void Pwm<Channels::Channel14>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM4, &TIM_OC4Init, period_, width);
}

template <>
Pwm<Channels::Channel14>::Pwm()
{
    Helper::initPwmClocks(TIM4, RCC_APB1Periph_TIM4, RCC_APB2Periph_GPIOB);
    Helper::configureGpio(GPIOB, GPIO_Pin_9, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
    period_ = Helper::configureTimer(TIM4, TIM_CounterMode_Up, 10000); // 10 KHz
    setPulse(0);
}


} // namespace bsp
