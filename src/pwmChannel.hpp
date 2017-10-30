#pragma once

#include "stm32f10x_conf.h"

#include <cassert>
#include <memory>

namespace pwm
{

enum class Channels
{
    CH0,
    CH1,
    CH2,
    CH3
};

#define TIM2_CH0_PIN GPIO_Pin_0
#define TIM2_CH1_PIN GPIO_Pin_1
#define TIM2_CH2_PIN GPIO_Pin_2
#define TIM2_CH3_PIN GPIO_Pin_3
#define TIM2_CH0_PORT GPIOA
#define TIM2_CH1_PORT GPIOA
#define TIM2_CH2_PORT GPIOA
#define TIM2_CH3_PORT GPIOA
#define TIM2_CH0_RCC RCC_APB2Periph_GPIOA
#define TIM2_CH1_RCC RCC_APB2Periph_GPIOA
#define TIM2_CH2_RCC RCC_APB2Periph_GPIOA
#define TIM2_CH3_RCC RCC_APB2Periph_GPIOA
#define TIM2_RCC RCC_APB1Periph_TIM2

#define TIM3_CH0_PIN GPIO_Pin_6
#define TIM3_CH1_PIN GPIO_Pin_7
#define TIM3_CH2_PIN GPIO_Pin_0
#define TIM3_CH3_PIN GPIO_Pin_1
#define TIM3_CH0_PORT GPIOA
#define TIM3_CH1_PORT GPIOA
#define TIM3_CH2_PORT GPIOB
#define TIM3_CH3_PORT GPIOB
#define TIM3_CH0_RCC RCC_APB2Periph_GPIOA
#define TIM3_CH1_RCC RCC_APB2Periph_GPIOA
#define TIM3_CH2_RCC RCC_APB2Periph_GPIOB
#define TIM3_CH3_RCC RCC_APB2Periph_GPIOB
#define TIM3_RCC RCC_APB1Periph_TIM3

#define TIM4_CH0_PIN GPIO_Pin_6
#define TIM4_CH1_PIN GPIO_Pin_7
#define TIM4_CH2_PIN GPIO_Pin_8
#define TIM4_CH3_PIN GPIO_Pin_9
#define TIM4_CH0_PORT GPIOB
#define TIM4_CH1_PORT GPIOB
#define TIM4_CH2_PORT GPIOB
#define TIM4_CH3_PORT GPIOB
#define TIM4_CH0_RCC RCC_APB2Periph_GPIOB
#define TIM4_CH1_RCC RCC_APB2Periph_GPIOB
#define TIM4_CH2_RCC RCC_APB2Periph_GPIOB
#define TIM4_CH3_RCC RCC_APB2Periph_GPIOB
#define TIM4_RCC RCC_APB1Periph_TIM4

class Channel
{
  public:
    Channel(u32 pin, GPIO_TypeDef* port, TIM_TypeDef* timer, u32 rccPeriph, u32 rccGpio, Channels chNr, bool alternate);
    virtual ~Channel();
    void setPulse(u8 width);
    u8 getPulse();

  private:
    void init();
    void initGpio();
    void initClocks();
    void initTimer(u32 freq);

    u32 channelPin_;
    GPIO_TypeDef* channelPort_;
    TIM_TypeDef* timer_;
    u32 rccPeriph_;
    u32 rccGpio_;
    Channels chNr_;
    u32 period_;
    bool alternate_;
    u8 pulse_;
};

class Channel0 : public Channel
{
  public:
    Channel0();
};

class Channel1 : public Channel
{
  public:
    Channel1();
};

class Channel2 : public Channel
{
  public:
    Channel2();
};

class Channel3 : public Channel
{
  public:
    Channel3();
};

class Channel4 : public Channel
{
  public:
    Channel4();
};

class Channel5 : public Channel
{
  public:
    Channel5();
};

class Channel6 : public Channel
{
  public:
    Channel6();
};

class Channel7 : public Channel
{
  public:
    Channel7();
};

class Channel8 : public Channel
{
  public:
    Channel8();
};

class Channel9 : public Channel
{
  public:
    Channel9();
};

class Channel10 : public Channel
{
  public:
    Channel10();
};

class Channel11 : public Channel
{
  public:
    Channel11();
};

class Channel12 : public Channel
{
  public:
    Channel12();
};

class Channel13 : public Channel
{
  public:
    Channel13();
};

std::unique_ptr<Channel> makeChannel(u8 nr);

} // namespace pwm
