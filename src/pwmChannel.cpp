#include "pwmChannel.hpp"

#include <cassert>
#include <cstdio>

#include "hal/utils/assert.hpp"

namespace pwm
{
Channel::Channel(u32 pin,
                 GPIO_TypeDef* port,
                 TIM_TypeDef* timer,
                 u32 rccPeriph,
                 u32 rccGpio,
                 Channels chNr,
                 bool alternate)
    : channelPin_(pin),
      channelPort_(port),
      timer_(timer),
      rccPeriph_(rccPeriph),
      rccGpio_(rccGpio),
      chNr_(chNr),
      alternate_(alternate),
      pulse_(0)
{
    init();
}

Channel::~Channel(){};

void Channel::setPulse(u8 width)
{
    HAL_ASSERT_MSG(width <= 100, "Pulse can be set only to 100%");
    TIM_OCInitTypeDef channel;

    TIM_OCStructInit(&channel);
    channel.TIM_OCMode = TIM_OCMode_PWM1;
    channel.TIM_OutputState = TIM_OutputState_Enable;
    float multiplier = (float)width / 100;
    u32 pulse = (float)period_ * multiplier;
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
    pulse_ = pulse;
}

u8 Channel::getPulse()
{
    return pulse_;
}

void Channel::init()
{
    initClocks();
    initGpio();
    // 10 KHz
    initTimer(10000);
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

    if (RCC_APB2Periph_TIM1 == rccPeriph_)
    {
        RCC_APB2PeriphClockCmd(rccPeriph_, ENABLE);
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(rccPeriph_, ENABLE);
    }
    RCC_APB2PeriphClockCmd(rccGpio_ | RCC_APB2Periph_AFIO, ENABLE);
}

void Channel::initTimer(u32 freq)
{
    TIM_TimeBaseInitTypeDef tim;
    TIM_TimeBaseStructInit(&tim);
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    u32 pre = SystemCoreClock / 1000000 - 1;
    tim.TIM_Prescaler = pre;
    period_ = 1000000 / freq;
    tim.TIM_Period = period_ - 1;
    TIM_TimeBaseInit(timer_, &tim);
    setPulse(0);
}

Channel0::Channel0()
    : Channel(GPIO_Pin_8,
              GPIOA,
              TIM1,
              RCC_APB2Periph_TIM1,
              RCC_APB2Periph_GPIOA,
              Channels::CH0,
              false)
{
}

Channel1::Channel1()
    : Channel(GPIO_Pin_9,
              GPIOA,
              TIM1,
              RCC_APB2Periph_TIM1,
              RCC_APB2Periph_GPIOA,
              Channels::CH1,
              false)
{
}

Channel2::Channel2()
    : Channel(GPIO_Pin_10,
              GPIOA,
              TIM1,
              RCC_APB2Periph_TIM1,
              RCC_APB2Periph_GPIOA,
              Channels::CH2,
              false)
{
}

Channel3::Channel3()
    : Channel(GPIO_Pin_11,
              GPIOA,
              TIM1,
              RCC_APB2Periph_TIM1,
              RCC_APB2Periph_GPIOA,
              Channels::CH3,
              false)
{
}

Channel4::Channel4()
    : Channel(GPIO_Pin_0,
              GPIOA,
              TIM2,
              RCC_APB1Periph_TIM2,
              RCC_APB2Periph_GPIOA,
              Channels::CH0,
              false)
{
}

Channel5::Channel5()
    : Channel(GPIO_Pin_1,
              GPIOA,
              TIM2,
              RCC_APB1Periph_TIM2,
              RCC_APB2Periph_GPIOA,
              Channels::CH1,
              false)
{
}

Channel6::Channel6()
    : Channel(GPIO_Pin_6,
              GPIOA,
              TIM3,
              RCC_APB1Periph_TIM3,
              RCC_APB2Periph_GPIOA,
              Channels::CH0,
              true)
{
}

Channel7::Channel7()
    : Channel(GPIO_Pin_7,
              GPIOA,
              TIM3,
              RCC_APB1Periph_TIM3,
              RCC_APB2Periph_GPIOA,
              Channels::CH1,
              true)
{
}

Channel8::Channel8()
    : Channel(GPIO_Pin_0,
              GPIOB,
              TIM3,
              RCC_APB1Periph_TIM3,
              RCC_APB2Periph_GPIOB,
              Channels::CH2,
              false)
{
}

Channel9::Channel9()
    : Channel(GPIO_Pin_1,
              GPIOB,
              TIM3,
              RCC_APB1Periph_TIM3,
              RCC_APB2Periph_GPIOB,
              Channels::CH3,
              false)
{
}

Channel10::Channel10()
    : Channel(GPIO_Pin_6,
              GPIOB,
              TIM4,
              RCC_APB1Periph_TIM4,
              RCC_APB2Periph_GPIOB,
              Channels::CH0,
              true)
{
}

Channel11::Channel11()
    : Channel(GPIO_Pin_7,
              GPIOB,
              TIM4,
              RCC_APB1Periph_TIM4,
              RCC_APB2Periph_GPIOB,
              Channels::CH1,
              true)
{
}

Channel12::Channel12()
    : Channel(GPIO_Pin_8,
              GPIOB,
              TIM4,
              RCC_APB1Periph_TIM4,
              RCC_APB2Periph_GPIOB,
              Channels::CH2,
              true)
{
}

Channel13::Channel13()
    : Channel(GPIO_Pin_9,
              GPIOB,
              TIM4,
              RCC_APB1Periph_TIM4,
              RCC_APB2Periph_GPIOB,
              Channels::CH3,
              true)
{
}

std::unique_ptr<Channel> makeChannel(u8 nr)
{
    HAL_ASSERT_MSG(nr >= 0 && nr < 14, "Wrong channel creation");
    switch (nr)
    {
        case 0:
            return std::unique_ptr<Channel>(new Channel0());
            break;
        case 1:
            return std::unique_ptr<Channel>(new Channel1());
            break;
        case 2:
            return std::unique_ptr<Channel>(new Channel2());
            break;
        case 3:
            return std::unique_ptr<Channel>(new Channel3());
            break;
        case 4:
            return std::unique_ptr<Channel>(new Channel4());
            break;
        case 5:
            return std::unique_ptr<Channel>(new Channel5());
            break;
        case 6:
            return std::unique_ptr<Channel>(new Channel6());
            break;
        case 7:
            return std::unique_ptr<Channel>(new Channel7());
            break;
        case 8:
            return std::unique_ptr<Channel>(new Channel8());
            break;
        case 9:
            return std::unique_ptr<Channel>(new Channel9());
            break;
        case 10:
            return std::unique_ptr<Channel>(new Channel10());
            break;
        case 11:
            return std::unique_ptr<Channel>(new Channel11());
            break;
        case 12:
            return std::unique_ptr<Channel>(new Channel12());
            break;
        case 13:
            return std::unique_ptr<Channel>(new Channel13());
            break;
    }
}

} // namespace pwm
