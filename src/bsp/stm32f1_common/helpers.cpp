#include "bsp/stm32f1_common/helpers.hpp"

#include <functional>

#include "hal/utils/assert.hpp"

namespace bsp
{

void Helper::configureGpio(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin   = pin;
    gpio.GPIO_Mode  = mode;
    gpio.GPIO_Speed = speed;
    GPIO_Init(port, &gpio);
}

uint32_t Helper::configureTimer(TIM_TypeDef* timer, uint16_t mode, uint16_t frequency)
{
    uint32_t period = 1000000 / frequency;

    TIM_TimeBaseInitTypeDef tim;
    TIM_TimeBaseStructInit(&tim);
    tim.TIM_CounterMode = mode;
    uint32_t pre        = SystemCoreClock / 1000000 - 1;
    tim.TIM_Prescaler   = pre;
    tim.TIM_Period      = period - 1;
    TIM_TimeBaseInit(timer, &tim);

    return period;
}

uint8_t Helper::setPwmPulse(TIM_TypeDef* timer, std::function<void(TIM_TypeDef*, TIM_OCInitTypeDef*)> ocInit, uint8_t period, uint8_t width)
{
    HAL_ASSERT_MSG(width <= 100, "Pulse can be set only to 100%");
    TIM_OCInitTypeDef channel;

    TIM_OCStructInit(&channel);
    channel.TIM_OCMode      = TIM_OCMode_PWM1;
    channel.TIM_OutputState = TIM_OutputState_Enable;
    float multiplier        = (float)width / 100;
    u32 pulse               = (float)period * multiplier;
    channel.TIM_Pulse       = pulse;
    ocInit(timer, &channel);
    TIM_Cmd(timer, ENABLE);
    return pulse;
}

void Helper::initPwmClocks(TIM_TypeDef* timer, u32 timerPeriphRcc, u32 gpioRcc)
{
    if (RCC_APB2Periph_TIM1 == timerPeriphRcc)
    {
        RCC_APB2PeriphClockCmd(timerPeriphRcc, ENABLE);
        TIM_CtrlPWMOutputs(timer, ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(timerPeriphRcc, ENABLE);
    }
    RCC_APB2PeriphClockCmd(gpioRcc | RCC_APB2Periph_AFIO, ENABLE);
}


} // namespace bsp