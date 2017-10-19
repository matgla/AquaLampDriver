// #include "dispatcher/ChannelHandler.hpp"
// #include "dispatcher/RtcHandler.hpp"
// #include "dispatcher/dispatcher.hpp"
// #include "logger.hpp"
// #include "pwm/channelsGroup.hpp"
// #include "pwmChannel.hpp"
// #include "rtc/rtc.hpp"
// #include "state_machine/bootloader_sm.hpp"
// #include "stm32includes.hpp"
// #include "types.hpp"
// #include "usart.hpp"
// #include "utils.hpp"
// #include <boost/sml.hpp>
// #include <cassert>
// #include <cstdlib>
// #include <cstring>
// #include <memory>
// #include <unistd.h>

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

TIM2_CH1 PA0h
TIM2_CH2 PA1
TIM2_CH3 PA2
TIM2_CH4 PA3
// */
// void initializeBoardLeds()
// {
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOB, &GPIO_InitStructure);
// }

#include "hal/serial/serial.hpp"
#include "logger/logger.hpp"

int main(void)
{
    logger::Logger logger("logger");

    logger.info() << "Booting system";
    // hal::serial::Serial serial("COM3", 57600);
    hal::serial::primarySerial.write("No hej:)");
    logger.info() << "Serial enabled";

    // SystemInit();
    // rtc::Rtc r;

    // rtc::Rtc::setTime(1, 5, 2017, 20, 12, 47);
    // initializeBoardLeds();
    // hw::USART<hw::USARTS::USART1_PP1>::getUsart().send("ready\n\0", 6);
    // GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    // Logger logger("boot\0");
    // // boost::sml::sm<BootLoaderSm> sm{logger};
    // dispatcher::Dispatcher hand;

    // // sm.process_event(evInitialize{});
    // // sm.process_event(evGetBootMode{});
    // // sm.process_event(evBoot{});

    // logger << Level::INFO << "Jadymy z tematem\n";

    // pwm::ChannelsGroup channels;
    // channels.configureChannel(0);

    // handler::IHandlerPtr channelHandler(new handler::ChannelHandler("ChannelHandler\0", channels));
    // handler::IHandlerPtr rtcHandler(new handler::RtcHandler("RtcHandler\0"));

    // hand.registerHandler(std::move(channelHandler));
    // hand.registerHandler(std::move(rtcHandler));

    // logger << Level::INFO << "Pwm Enabled\n";
    // //  TIM_Cmd(TIM2, ENABLE);
    // // logger << Level::INFO << "NVIC reconfigured\n";
    // char msg[100];
    // int i = 0;
    // while (1)
    // {
    //     if (hw::USART<hw::USARTS::USART1_PP1>::getUsart().size())
    //     {
    //         while (hw::USART<hw::USARTS::USART1_PP1>::getUsart().size())
    //         {
    //             char c = hw::USART<hw::USARTS::USART1_PP1>::getUsart().read();
    //             if (c == '\n')
    //             {
    //                 msg[i] = 0;
    //                 hand.handle(msg);
    //                 i = 0;
    //                 logger.info() << "event proceeded\n";
    //             }
    //             else
    //             {
    //                 msg[i++] = c;
    //             }
    //         }
    //         if (i > 100)
    //         {
    //             logger.info() << "Buffer overflow!\n";
    //             i = 0;
    //             continue;
    //         }
    //     }
    //     // sm.process_event(evInitialize{});
    // }
}
