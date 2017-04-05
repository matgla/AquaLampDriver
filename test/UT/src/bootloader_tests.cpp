#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <unistd.h>

#include "bootloader.hpp"

#include "messages.hpp"
#include "usart.hpp"

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "rcc_mock.hpp"
#include "usart_mock.hpp"

class BootLoaderTests : public ::testing::Test
{
  public:
    SAFE_MOCK(RCC_AHB1PeriphClockCmd, rcc1Mock_);
    SAFE_MOCK(RCC_APB2PeriphClockCmd, rcc2Mock_);
    SAFE_MOCK(GPIO_PinAFConfig, gpioAfMock_);
    SAFE_MOCK(GPIO_Init, gpioInitMock_);
    SAFE_MOCK(NVIC_Init, nvicInitMock_);
    SAFE_MOCK(USART_SendData, usartSendMock_);
    SAFE_MOCK(USART_GetFlagStatus, usartGetFlagMock_);
    SAFE_MOCK(USART_GetITStatus, usartGetItMock_);
    BootLoaderTests()
        : rcc1Mock_(GET_MOCK(RCC_AHB1PeriphClockCmd)),
          rcc2Mock_(GET_MOCK(RCC_APB2PeriphClockCmd)),
          gpioAfMock_(GET_MOCK(GPIO_PinAFConfig)),
          gpioInitMock_(GET_MOCK(GPIO_Init)),
          nvicInitMock_(GET_MOCK(NVIC_Init)),
          usartSendMock_(GET_MOCK(USART_SendData)),
          usartGetFlagMock_(GET_MOCK(USART_GetFlagStatus)),
          usartGetItMock_(GET_MOCK(USART_GetITStatus))
    {
    }

    virtual void SetUp()
    {
        if (!hw::USART<hw::USARTS::USART1_PP1>::initialized())
        {
            expectInitialization();
        }
        else
        {
            hw::USART<hw::USARTS::USART1_PP1>::getUsart().flush();
        }
    }
    virtual void TearDown()
    {
    }
};

TEST_F(BootLoaderTests, shouldSetReceiverCallback)
{
    Logger logger("test\0", 2);
    BootLoader bootloader(logger);
    ClientInfo info;
    std::memcpy(info.name_, "PC_12\0", 7);
    info.fd_ = static_cast<u8>(FileDescriptors::COMMUNICATION);

    logger << Level::INFO << "Name: " << info.name_ << "\n";

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    u8 size = sizeof(ClientInfo);

    u8* payload = reinterpret_cast<u8*>(&info);

    EXPECT_EQ(payload[0], info.fd_);
    EXPECT_EQ(payload[1], info.id_);
    EXPECT_EQ(payload[2], info.name_[0]);
    EXPECT_EQ(payload[3], info.name_[1]);
    EXPECT_EQ(payload[4], info.name_[2]);
    EXPECT_EQ(payload[5], info.name_[3]);
    EXPECT_EQ(payload[6], info.name_[4]);

    expectSendData(1); // ack size
    expectSendData(static_cast<u8>(Messages::ACK));

    usart.receive(size);
    for (int i = 0; i < size; i++)
    {
        usart.receive(payload[i]);
    }

    EXPECT_EQ(true, true);
}
