#include "stm32includes.hpp"
#include <boost/sml.hpp>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "logger.hpp"
#include "state_machine/bootloader_sm.hpp"
#include "handler.hpp"
#include "types.h"
#include "utils.hpp"
#include "usart.hpp"
#include "pwmChannel.hpp"

// __IO uint32_t uwAsynchPrediv = 0;
// __IO uint32_t uwSynchPrediv = 0;
//   uint8_t aShowTime[50] = {0};

// void RTC_Config()
// {
//     RTC_DateTypeDef rtc;
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//     PWR_BackupAccessCmd(ENABLE);
//     RCC_LSICmd(ENABLE);
//     while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET) {}
//     RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
//     /* ck_spre(1Hz) = RTCCLK(LSI) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
//   uwSynchPrediv = 0xFF;
//   uwAsynchPrediv = 0x7F;
//   RCC_RTCCLKCmd(ENABLE);

//   /* Wait for RTC APB registers synchronisation */
//   RTC_WaitForSynchro();

//   /* Configure the RTC data register and RTC prescaler */
//   RTC_InitStructure.RTC_AsynchPrediv = uwAsynchPrediv;
//   RTC_InitStructure.RTC_SynchPrediv = uwSynchPrediv;
//   RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
//   RTC_Init(&RTC_InitStructure);

//   /* Set the alarm 05h:20min:30s */
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x05;
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x20;
//   RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x30;
//   RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
//   RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
//   RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;

//   /* Configure the RTC Alarm A register */
//   RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

//   /* Enable RTC Alarm A Interrupt */
//   RTC_ITConfig(RTC_IT_ALRA, ENABLE);

//   /* Enable the alarm */
//   RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

//   RTC_ClearFlag(RTC_FLAG_ALRAF);

//   /* Set the date: Friday January 11th 2013 */
//   RTC_DateStructure.RTC_Year = 0x13;
//   RTC_DateStructure.RTC_Month = RTC_Month_January;
//   RTC_DateStructure.RTC_Date = 0x11;
//   RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Saturday;
//   RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);

//   /* Set the time to 05h 20mn 00s AM */
//   RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
//   RTC_TimeStructure.RTC_Hours   = 0x05;
//   RTC_TimeStructure.RTC_Minutes = 0x20;
//   RTC_TimeStructure.RTC_Seconds = 0x00;

//   RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

//   /* Indicator for the RTC configuration */
//   RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
// }

/*
TIM3_CH1 PA6
TIM3_CH2 PA7
TIM3_CH3 PB0
TIM4_CH4 PB1

TIM2_CH1 PA0
TIM2_CH2 PA1
TIM2_CH3 PA2
TIM2_CH4 PA3
*/
void initializeBoardLeds()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
extern "C" {
void TIM2_IRQHandler();
}
void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12))
            GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        else
            GPIO_SetBits(GPIOB, GPIO_Pin_12);
    }
}

int main(void)
{
    SystemInit();
    initializeBoardLeds();
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().send("ready\n\0", 6);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    Logger logger("boot\0");
    // boost::sml::sm<BootLoaderSm> sm{logger};
    handler::Handler hand;

    // sm.process_event(evInitialize{});
    // sm.process_event(evGetBootMode{});
    // sm.process_event(evBoot{});

    logger << Level::INFO << "Jadymy z tematem\n";

    // GPIO_InitTypeDef gpio;
    // TIM_TimeBaseInitTypeDef tim;
    // NVIC_InitTypeDef nvic;
    // TIM_OCInitTypeDef channel;

    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    // logger << Level::INFO << "Timer enabled\n";

    // GPIO_StructInit(&gpio);
    // gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_0 | GPIO_Pin_1;
    // gpio.GPIO_Speed = GPIO_Speed_50MHz;
    // gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_Init(GPIOB, &gpio);

    // TIM_TimeBaseStructInit(&tim);
    // tim.TIM_CounterMode = TIM_CounterMode_Up;
    // tim.TIM_Prescaler = 101 - 1;
    // tim.TIM_Period = 100 - 1;
    // TIM_TimeBaseInit(TIM4, &tim);

    // TIM_OCStructInit(&channel);
    // channel.TIM_OCMode = TIM_OCMode_PWM1;
    // channel.TIM_OutputState = TIM_OutputState_Enable;
    // channel.TIM_Pulse = 50;
    // TIM_OC1Init(TIM4, &channel);
    // channel.TIM_Pulse = 60;
    // TIM_OC2Init(TIM4, &channel);
    // channel.TIM_Pulse = 70;
    // TIM_OC3Init(TIM4, &channel);
    // channel.TIM_Pulse = 80;
    // TIM_OC4Init(TIM4, &channel);

    // TIM_Cmd(TIM4, ENABLE);

    // //
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // logger << Level::INFO << "Timer enabled\n";

    // GPIO_StructInit(&gpio);
    // gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    // gpio.GPIO_Speed = GPIO_Speed_50MHz;
    // gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_Init(GPIOA, &gpio);

    // TIM_TimeBaseStructInit(&tim);
    // tim.TIM_CounterMode = TIM_CounterMode_Up;
    // tim.TIM_Prescaler = 101 - 1;
    // tim.TIM_Period = 100 - 1;
    // TIM_TimeBaseInit(TIM3, &tim);

    // TIM_OCStructInit(&channel);
    // channel.TIM_OCMode = TIM_OCMode_PWM1;
    // channel.TIM_OutputState = TIM_OutputState_Enable;
    // channel.TIM_Pulse = 10;
    // TIM_OC1Init(TIM3, &channel);
    // channel.TIM_Pulse = 50;
    // TIM_OC2Init(TIM3, &channel);
    // channel.TIM_Pulse = 80;
    // TIM_OC3Init(TIM3, &channel);
    // channel.TIM_Pulse = 95;
    // TIM_OC4Init(TIM3, &channel);

    // TIM_Cmd(TIM3, ENABLE);

    // //

    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // logger << Level::INFO << "Timer enabled\n";

    // GPIO_StructInit(&gpio);
    // gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    // gpio.GPIO_Speed = GPIO_Speed_50MHz;
    // gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_Init(GPIOA, &gpio);

    // TIM_TimeBaseStructInit(&tim);
    // tim.TIM_CounterMode = TIM_CounterMode_Up;
    // tim.TIM_Prescaler = 101 - 1;
    // tim.TIM_Period = 100 - 1;
    // TIM_TimeBaseInit(TIM2, &tim);

    // TIM_OCStructInit(&channel);
    // channel.TIM_OCMode = TIM_OCMode_PWM1;
    // channel.TIM_OutputState = TIM_OutputState_Enable;
    // channel.TIM_Pulse = 10;
    // TIM_OC1Init(TIM2, &channel);
    // channel.TIM_Pulse = 20;
    // TIM_OC2Init(TIM2, &channel);
    // channel.TIM_Pulse = 30;
    // TIM_OC3Init(TIM2, &channel);
    // channel.TIM_Pulse = 40;
    // TIM_OC4Init(TIM2, &channel);

    // TIM_Cmd(TIM2, ENABLE);
    pwm::Channel ch0(TIM2_CH0_PIN, TIM2_CH0_PORT, TIM2, TIM2_RCC, TIM2_CH0_RCC, pwm::Channels::CH0);
    ch0.setPulse(20);
    logger << Level::INFO << "Pwm Enabled\n";
    //  TIM_Cmd(TIM2, ENABLE);
    // logger << Level::INFO << "NVIC reconfigured\n";
    char msg[100];
    int i = 0;
    while (1)
    {
        if (hw::USART<hw::USARTS::USART1_PP1>::getUsart().size())
        {
            while (hw::USART<hw::USARTS::USART1_PP1>::getUsart().size())
            {
                char c = hw::USART<hw::USARTS::USART1_PP1>::getUsart().read();
                if (c == '\n')
                {
                    msg[i] = 0;
                    // char *m;
                    // m = strtok(msg, " ");
                    // while (m != nullptr)
                    // {
                    //     logger.info() << "Get message: " << m << "\n";
                    //     m = strtok(nullptr, " ");
                    // }
                    hand.handle(msg);
                    i = 0;
                    logger.info() << "event proceeded\n";
                }
                else
                {
                    msg[i++] = c;
                }
            }
            if (i > 100)
            {
                logger.info() << "Buffer overflow!\n";
                i = 0;
                continue;
            }
        }
        // sm.process_event(evInitialize{});
    }
}

void assert_failed(u8 *file, u32 line)
{
    write(0, file, strlen((char *)file));
    write(0, ":", 1);
    char buf[10];
    utils::itoa(line, buf, 10);
    write(0, buf, strlen(buf));
    write(0, " assertion failed!", 18);
    while (true)
    {
    }
}
