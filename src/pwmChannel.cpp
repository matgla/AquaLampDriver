#include "pwmChannel.hpp"

#include <cassert>
#include <cstdio>

namespace pwm
{
Channel::Channel(u32 pin,
                 GPIO_TypeDef *port,
                 TIM_TypeDef *timer,
                 u32 rccPeriph,
                 u32 rccGpio,
                 Channels chNr) : channelPin_(pin),
                                  channelPort_(port),
                                  timer_(timer),
                                  rccPeriph_(rccPeriph),
                                  rccGpio_(rccGpio),
                                  chNr_(chNr)
{
    init();
}

void Channel::setPulse(u8 width)
{
    assert(width <= 100);
    TIM_OCInitTypeDef channel;

    TIM_OCStructInit(&channel);
    channel.TIM_OCMode = TIM_OCMode_PWM1;
    channel.TIM_OutputState = TIM_OutputState_Enable;
    float multiplier = (float)width / 100;
    printf("multiplifer %f\n", multiplier);
    u32 pulse = period_ * multiplier;
    printf("pulse:  %d, period: %d\n", pulse, period_);
    channel.TIM_Pulse = pulse;
    //TIM_Cmd(timer_, DISABLE);
    switch (chNr_)
    {
    case Channels::CH0:
    {
        TIM_OC1Init(timer_, &channel);
    }
    break;

    case Channels::CH1:
    {
        TIM_OC2Init(timer_, &channel);
    }
    break;

    case Channels::CH2:
    {
        TIM_OC3Init(timer_, &channel);
    }
    break;

    case Channels::CH3:
    {
        TIM_OC4Init(timer_, &channel);
    }
    break;
    }
    TIM_Cmd(timer_, ENABLE);
}

void Channel::init()
{
    initClocks();
    initGpio();
    // 36 KHz
    initTimer(100000);
}

void Channel::initGpio()
{
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = channelPin_;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(channelPort_, &gpio);
}

void Channel::initClocks()
{
    RCC_APB1PeriphClockCmd(rccPeriph_, ENABLE);
    RCC_APB2PeriphClockCmd(rccGpio_, ENABLE);
}

void Channel::initTimer(u32 freq)
{
    TIM_TimeBaseInitTypeDef tim;
    TIM_TimeBaseStructInit(&tim);
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    u32 pre = SystemCoreClock / 1000000 - 1;
    tim.TIM_Prescaler = pre;
    printf("Core clock: %d, pre: %d\n", SystemCoreClock, pre);
    period_ = 1000000 / freq;
    tim.TIM_Period = period_ - 1;
    TIM_TimeBaseInit(timer_, &tim);

    setPulse(0);
}

} // namespace pwm