#include "bsp/pwm.hpp"

#include "bsp/stm32f1_common/helpers.hpp"

namespace bsp
{

template <>
void Pwm<Channels::Channel1>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM1, &TIM_OC1Init, period_, width);
}

template <>
void Pwm<Channels::Channel2>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM1, &TIM_OC2Init, period_, width);
}

template <>
void Pwm<Channels::Channel3>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM1, &TIM_OC3Init, period_, width);
}

template <>
void Pwm<Channels::Channel4>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM1, &TIM_OC4Init, period_, width);
}

template <>
void Pwm<Channels::Channel5>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM2, &TIM_OC1Init, period_, width);
}

template <>
void Pwm<Channels::Channel6>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM2, &TIM_OC2Init, period_, width);
}

template <>
void Pwm<Channels::Channel7>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM2, &TIM_OC3Init, period_, width);
}

template <>
void Pwm<Channels::Channel8>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM2, &TIM_OC4Init, period_, width);
}

template <>
void Pwm<Channels::Channel9>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM3, &TIM_OC1Init, period_, width);
}

template <>
void Pwm<Channels::Channel10>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM3, &TIM_OC2Init, period_, width);
}

template <>
void Pwm<Channels::Channel11>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM3, &TIM_OC3Init, period_, width);
}

template <>
void Pwm<Channels::Channel12>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM3, &TIM_OC4Init, period_, width);
}

template <>
void Pwm<Channels::Channel13>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM4, &TIM_OC1Init, period_, width);
}

template <>
void Pwm<Channels::Channel14>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM4, &TIM_OC2Init, period_, width);
}

template <>
void Pwm<Channels::Channel15>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM4, &TIM_OC3Init, period_, width);
}

template <>
void Pwm<Channels::Channel16>::setPulse(u8 width)
{
    pulse_ = Helper::setPwmPulse(TIM4, &TIM_OC4Init, period_, width);
}

uint32_t configureHardware(TIM_TypeDef* timer, u32 timerPeriphRcc, u32 gpioRcc, GPIO_TypeDef* port, uint16_t pin)
{
    Helper::initPwmClocks(timer, timerPeriphRcc, gpioRcc);
    Helper::configureGpio(port, pin, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
    return Helper::configureTimer(timer, TIM_CounterMode_Up, 10000); // 10 KHz
}

template <>
Pwm<Channels::Channel1>::Pwm()
{
    period_ = configureHardware(TIM1, RCC_APB2Periph_TIM1, RCC_APB2Periph_GPIOA,
                                GPIOA, GPIO_Pin_8);
    setPulse(0);
}

template <>
Pwm<Channels::Channel2>::Pwm()
{
    period_ = configureHardware(TIM1, RCC_APB2Periph_TIM1, RCC_APB2Periph_GPIOA,
                                GPIOA, GPIO_Pin_9);
    setPulse(0);
}

template <>
Pwm<Channels::Channel3>::Pwm()
{
    period_ = configureHardware(TIM1, RCC_APB2Periph_TIM1, RCC_APB2Periph_GPIOA,
                                GPIOA, GPIO_Pin_10);
    setPulse(0);
}

template <>
Pwm<Channels::Channel4>::Pwm()
{
    period_ = configureHardware(TIM1, RCC_APB2Periph_TIM1, RCC_APB2Periph_GPIOA,
                                GPIOA, GPIO_Pin_11);
    setPulse(0);
}

template <>
Pwm<Channels::Channel5>::Pwm()
{
    period_ = configureHardware(TIM2, RCC_APB1Periph_TIM2, RCC_APB2Periph_GPIOA,
                                GPIOA, GPIO_Pin_0);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel6>::Pwm()
{
    period_ = configureHardware(TIM2, RCC_APB1Periph_TIM2, RCC_APB2Periph_GPIOA,
                                GPIOA, GPIO_Pin_1);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel7>::Pwm()
{
    period_ = configureHardware(TIM2, RCC_APB1Periph_TIM2, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_10);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel8>::Pwm()
{
    period_ = configureHardware(TIM2, RCC_APB1Periph_TIM2, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_11);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel9>::Pwm()
{
    period_ = configureHardware(TIM3, RCC_APB1Periph_TIM3, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_4);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
    setPulse(0);
}

template <>
Pwm<Channels::Channel10>::Pwm()
{
    period_ = configureHardware(TIM3, RCC_APB1Periph_TIM3, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_5);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel11>::Pwm()
{
    period_ = configureHardware(TIM3, RCC_APB1Periph_TIM3, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_0);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel12>::Pwm()
{
    period_ = configureHardware(TIM3, RCC_APB1Periph_TIM3, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_1);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel13>::Pwm()
{
    period_ = configureHardware(TIM4, RCC_APB1Periph_TIM4, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_6);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    setPulse(0);
}

template <>
Pwm<Channels::Channel14>::Pwm()
{
    period_ = configureHardware(TIM4, RCC_APB1Periph_TIM4, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_7);
    setPulse(0);
}

template <>
Pwm<Channels::Channel15>::Pwm()
{
    period_ = configureHardware(TIM4, RCC_APB1Periph_TIM4, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_8);
    setPulse(0);
}

template <>
Pwm<Channels::Channel16>::Pwm()
{
    period_ = configureHardware(TIM4, RCC_APB1Periph_TIM4, RCC_APB2Periph_GPIOB,
                                GPIOB, GPIO_Pin_9);
    setPulse(0);
}


} // namespace bsp
