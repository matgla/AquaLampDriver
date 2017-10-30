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
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int main(void)
{
    SystemInit();
    rtc::Rtc r;
    rtc::Rtc::setTime(1, 5, 2017, 20, 12, 47);
    initializeBoardLeds();
    initializeButtons();
    hw::USART<hw::USARTS::USART2_PP1>::getUsart().send("ready\n\0", 6);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    Logger logger("boot\0");
    dispatcher::Dispatcher hand;


    logger << Level::INFO << "Jadymy z tematem\n";

    pwm::ChannelsGroup channels;
    channels.configureAllChannels();

    channels.setChannelPulse(0, 100);
    channels.setChannelPulse(1, 100);
    channels.setChannelPulse(2, 100);
    channels.setChannelPulse(3, 100);
    channels.setChannelPulse(4, 100);
    channels.setChannelPulse(5, 100);
    channels.setChannelPulse(6, 100);
    channels.setChannelPulse(7, 100);
    channels.setChannelPulse(8, 100);
    channels.setChannelPulse(9, 100);
    channels.setChannelPulse(10, 100);
    channels.setChannelPulse(11, 100);
    channels.setChannelPulse(12, 100);
    channels.setChannelPulse(13, 100);

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
        }
        // sm.process_event(evInitialize{});
    }
}
