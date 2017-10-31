#include "dispatcher/ChannelHandler.hpp"
#include "dispatcher/RtcHandler.hpp"
#include "dispatcher/dispatcher.hpp"
#include "logger.hpp"
#include "pwm/channelsGroup.hpp"
#include "pwmChannel.hpp"
#include "rtc/rtc.hpp"
#include "state_machine/bootloader_sm.hpp"
#include "stm32includes.hpp"
#include "types.hpp"
#include "usart.hpp"
#include "utils.hpp"
#include <boost/sml.hpp>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unistd.h>

extern uint32_t SystemCoreClock;

u8 initializeSysTick(u32 time_us)
{
    if (time_us == 0)
        return false;
    printf("Core clock: %d", SystemCoreClock);
    if (SysTick_Config(SystemCoreClock / 1000000 * time_us) != 0)
    {
        return false;
    }
    return true;
}

void initializeBoardLeds()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void initializeButtons()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int main(void)
{
    SystemInit();

    Logger logger("boot\0");

    logger.info() << "Before: " << BKP_ReadBackupRegister(BKP_DR1) << "\n";
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xabcd)
    {
        rtc::Rtc r;
        logger.info() << "set time\n";
        rtc::Rtc::setTime(1, 5, 2017, 20, 12, 47);
        BKP_WriteBackupRegister(BKP_DR1, 0xabcd);
        logger.info() << "Wrote: " << 0xabcd << " Read: " << BKP_ReadBackupRegister(BKP_DR1) << "\n";
    }
    else
    {
        RTC_WaitForSynchro();
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();

        NVIC_InitTypeDef nvic;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
        nvic.NVIC_IRQChannel = RTC_IRQn;
        nvic.NVIC_IRQChannelPreemptionPriority = 1;
        nvic.NVIC_IRQChannelSubPriority = 0;
        nvic.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&nvic);
    }


    initializeBoardLeds();
    initializeButtons();
    initializeSysTick(1000);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    dispatcher::Dispatcher hand;


    logger << Level::INFO << "Jadymy z tematem\n";

    pwm::ChannelsGroup channels;
    channels.configureAllChannels();

    u8 power = 0;
    bool rise = true;
    bool shine = false;
    rtc::Rtc::setHandler([&channels, &power, &logger, &shine, &rise]() {
        if (rise)
        {
            if (power == 100)
            {
                rise = false;
                rtc::Rtc::setAlarm(rtc::Rtc::getTime() + 10);
                return;
            }
            logger.info() << "more light\n";
            power += 5;
            channels.setChannelPulse(0, power);
            channels.setChannelPulse(1, power);
            channels.setChannelPulse(2, power);
            channels.setChannelPulse(3, power);
            channels.setChannelPulse(4, power);
            channels.setChannelPulse(5, power);
            channels.setChannelPulse(6, power);
            channels.setChannelPulse(7, power);
            channels.setChannelPulse(8, power);
            channels.setChannelPulse(9, power);
            channels.setChannelPulse(10, power);
            channels.setChannelPulse(11, power);
            channels.setChannelPulse(12, power);
            channels.setChannelPulse(13, power);
            rtc::Rtc::setAlarm(rtc::Rtc::getTime() + 1);
        }
        if (!rise && !shine)
        {
            shine = true;
            rtc::Rtc::setAlarm(rtc::Rtc::getTime() + 1);
            return;
        }
        if (shine)
        {
            if (power == 0)
            {
                return;
            }
            logger.info() << "less light\n";
            power -= 5;
            channels.setChannelPulse(0, power);
            channels.setChannelPulse(1, power);
            channels.setChannelPulse(2, power);
            channels.setChannelPulse(3, power);
            channels.setChannelPulse(4, power);
            channels.setChannelPulse(5, power);
            channels.setChannelPulse(6, power);
            channels.setChannelPulse(7, power);
            channels.setChannelPulse(8, power);
            channels.setChannelPulse(9, power);
            channels.setChannelPulse(10, power);
            channels.setChannelPulse(11, power);
            channels.setChannelPulse(12, power);
            channels.setChannelPulse(13, power);
            rtc::Rtc::setAlarm(rtc::Rtc::getTime() + 1);
        }

    });
    rtc::Rtc::setAlarm(rtc::Rtc::getTime() + 1);

    // channels.setChannelPulse(0, 100);
    // channels.setChannelPulse(1, 100);
    // channels.setChannelPulse(2, 100);
    // channels.setChannelPulse(3, 100);
    // channels.setChannelPulse(4, 100);
    // channels.setChannelPulse(5, 100);
    // channels.setChannelPulse(6, 100);
    // channels.setChannelPulse(7, 100);
    // channels.setChannelPulse(8, 100);
    // channels.setChannelPulse(9, 100);
    // channels.setChannelPulse(10, 100);
    // channels.setChannelPulse(11, 100);
    // channels.setChannelPulse(12, 100);
    // channels.setChannelPulse(13, 100);

    handler::IHandlerPtr channelHandler(new handler::ChannelHandler("ChannelHandler\0", channels));
    handler::IHandlerPtr rtcHandler(new handler::RtcHandler("RtcHandler\0"));

    hand.registerHandler(std::move(channelHandler));
    hand.registerHandler(std::move(rtcHandler));

    logger << Level::INFO << "Pwm Enabled\n";
    //  TIM_Cmd(TIM2, ENABLE);
    // logger << Level::INFO << "NVIC reconfigured\n";
    char msg[100];
    int i = 0;

    u8 ch = 0;

    while (1)
    {
        if (hw::USART<hw::USARTS::USART2_PP1>::getUsart().size())
        {
            while (hw::USART<hw::USARTS::USART2_PP1>::getUsart().size())
            {
                char c = hw::USART<hw::USARTS::USART2_PP1>::getUsart().read();
                if (c == '\n')
                {
                    msg[i] = 0;
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

        // buttom down
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14))
        {
            logger.info() << "Pressed button down\n";
            if (ch == 0)
            {
                ch = 13;
            }
            else
            {
                --ch;
            }
            logger.info() << "Current channel = " << ch << "\n";
            delay(100);
        }
        // buttom up
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
        {
            logger.info() << "Pressed button up\n";

            if (ch == 13)
            {
                ch = 0;
            }
            else
            {
                ++ch;
            }
            logger.info() << "Current channel = " << ch << "\n";
            delay(100);
        }
        // buttom left
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))
        {
            logger.info() << "Pressed button left\n";

            auto pulse = channels.getChannelPulse(ch);
            if (pulse < 20)
            {
                pulse = 0;
            }
            else
            {
                pulse -= 20;
            }
            channels.setChannelPulse(ch, pulse);
            delay(100);
        }
        // buttom right
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
        {
            logger.info() << "Pressed button right\n";

            auto pulse = channels.getChannelPulse(ch);
            if (pulse > 80)
            {
                pulse = 100;
            }
            else
            {
                pulse += 20;
            }
            channels.setChannelPulse(ch, pulse);
            delay(100);
        }
        // sm.process_event(evInitialize{});
    }
}
