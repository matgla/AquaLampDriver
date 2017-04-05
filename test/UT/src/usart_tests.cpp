#include "stm32f4xx_usart.h"

#include "gtest/gtest.h"

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "rcc_mock.hpp"
#include "usart_mock.hpp"

#include "usart.hpp"

class UsartShould : public ::testing::Test
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

    UsartShould()
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

TEST_F(UsartShould, HandleIrqRequestCorrect)
{
    const u16 EXPECTED_VALUE = 4;
    USART1->DR = EXPECTED_VALUE;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(RESET);
    USART1_IRQHandler();
    EXPECT_EQ(usart.getBuffer().size(), 0);

    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(SET);
    USART1_IRQHandler();
    EXPECT_EQ(usart.getBuffer().size(), 1);
    EXPECT_EQ(usart.getBuffer().getByte(), EXPECTED_VALUE);
    EXPECT_EQ(usart.getBuffer().size(), 0);
}

TEST_F(UsartShould, ShoudAckAfterReceive)
{
    const u16 EXPECTED_VALUE = 4;
    const u16 EXPECTED_SIZE = 1;
    USART1->DR = EXPECTED_SIZE;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(SET);
    USART1_IRQHandler();
    EXPECT_TRUE(usart.isTransmissionOngoing());
    USART1->DR = EXPECTED_VALUE;

    Ack ack;
    usart.getBuffer().write(reinterpret_cast<u8*>(&ack), sizeof(Ack));

    EXPECT_CALL(USART_GetITStatus, USART1, USART_IT_RXNE).willReturn(SET);
    USART1_IRQHandler();
    EXPECT_FALSE(usart.isTransmissionOngoing());
    EXPECT_EQ(usart.getBuffer().getByte(), EXPECTED_SIZE);
    EXPECT_EQ(usart.getBuffer().getByte(), EXPECTED_VALUE);
}

TEST_F(UsartShould, SendByteCorrectly)
{
    char EXPECTED_SEND_DATA = 156;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    expectSendData(EXPECTED_SEND_DATA);

    Ack ack;
    usart.getBuffer().write(reinterpret_cast<u8*>(&ack), sizeof(Ack));

    usart.send(EXPECTED_SEND_DATA);
    usart.waitForAck(5);
}

TEST_F(UsartShould, SendStringCorrectly)
{
    char EXPECTED_SEND_DATA[100] = "DataTo send\0";

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    Ack ack;
    usart.getBuffer().write(reinterpret_cast<u8*>(&ack), sizeof(Ack));
    expectSendData(EXPECTED_SEND_DATA);

    usart.send(EXPECTED_SEND_DATA);
    usart.waitForAck(5);
}

TEST_F(UsartShould, SendDataCorrectlyWhenBufferIsNotEmpty)
{
    char DATA_IN_BUFFER[15] = "1Ab2a\0";
    char EXPECTED_SEND_DATA[15] = "DataTo send\0";

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    usart.getBuffer().write(DATA_IN_BUFFER);

    Ack ack;
    usart.getBuffer().write(reinterpret_cast<u8*>(&ack), sizeof(Ack));

    expectSendData(EXPECTED_SEND_DATA);

    usart.send(EXPECTED_SEND_DATA);
    usart.waitForAck(5);

    std::string data;

    while (usart.getBuffer().size())
    {
        data += usart.getBuffer().getByte();
    }

    EXPECT_EQ(DATA_IN_BUFFER, data);
}

TEST_F(UsartShould, SendDataCorrectlyWhenDataArriveAfterAck)
{
    char DATA_IN_BUFFER[15] = "1Ab2a\0";
    char DATA_AFTER_ACK[15] = "aaabsd\0";
    char EXPECTED_SEND_DATA[15] = "DataTo send\0";
    std::string EXPECTED_OUTPUT = DATA_IN_BUFFER;
    EXPECTED_OUTPUT += DATA_AFTER_ACK;

    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    usart.getBuffer().write(DATA_IN_BUFFER);

    Ack ack;
    usart.getBuffer().write(reinterpret_cast<u8*>(&ack), sizeof(Ack));

    usart.getBuffer().write(DATA_AFTER_ACK);

    expectSendData(EXPECTED_SEND_DATA);

    usart.send(EXPECTED_SEND_DATA);
    usart.waitForAck(5);

    std::string data;

    while (usart.getBuffer().size())
    {
        data += usart.getBuffer().getByte();
    }

    EXPECT_EQ(EXPECTED_OUTPUT, data);
}

TEST_F(UsartShould, ReceiveMessageCorrectly)
{
    const u8 EXPECTED_FD = 6;
    RequestDownload msg;
    msg.fd_ = EXPECTED_FD;
    const u8 EXPECTED_SIZE = sizeof(msg);
    const u8 EXPECTED_MSG_TYPE = static_cast<u8>(Messages::SW_DWN_REQ);

    EXPECT_EQ(msg.id_, EXPECTED_MSG_TYPE);
    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    usart.getBuffer().write(EXPECTED_SIZE);
    usart.getBuffer().write(reinterpret_cast<u8*>(&msg), sizeof(RequestDownload));

    u8 buffer[255];
    usart.getMessage(buffer);

    RequestDownload receivedMessage;
    memcpy(&receivedMessage, buffer, sizeof(RequestDownload));
    EXPECT_EQ(receivedMessage.id_, EXPECTED_MSG_TYPE);
    EXPECT_EQ(receivedMessage.fd_, EXPECTED_FD);
}

TEST_F(UsartShould, SendMessageCorrectly)
{
    const u8 EXPECTED_FD = 6;
    RequestDownload msg;
    msg.fd_ = EXPECTED_FD;
    const u8 EXPECTED_SIZE = sizeof(msg);
    const u8 EXPECTED_MSG_TYPE = static_cast<u8>(Messages::SW_DWN_REQ);

    EXPECT_EQ(msg.id_, EXPECTED_MSG_TYPE);
    auto& usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();

    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, EXPECTED_SIZE);
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);

    expectSendData(EXPECTED_FD);
    expectSendData(EXPECTED_MSG_TYPE);

    usart.getBuffer().write(static_cast<u8>(Messages::ACK));

    usart.sendMessage(reinterpret_cast<u8*>(&msg), sizeof(msg));
}