#include "usart.hpp"
#include "logger.hpp"
#include "utils.hpp"

#include <cstdint>

void usart_put(USART_TypeDef* USARTx, const char* str)
{

    /* Go through entire string */

    while (*str)
    {

        /* Wait to be ready, buffer empty */

        USART_WAIT(USARTx);

        /* Send data */

        USARTx->DR = (uint16_t)(*str++ & 0x01FF);

        /* Wait to be ready, buffer empty */

        USART_WAIT(USARTx);
    }
}

namespace hw
{

template <USARTS UsartNumber>
USART<UsartNumber>& USART<UsartNumber>::getUsart()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
    static USART s;
    return s;
}

template <USARTS UsartNumber>
ReaderWriterBuffer<BUFFER_SIZE>& USART<UsartNumber>::getBuffer()
{
    return buffer_;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(char ch)
{
    wait();
    USART_SendData(USARTx_, ch);
    wait();
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(char* str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        send(str[i]);
    }
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(u8* str, int size)
{
    for (int i = 0; i < size; ++i)
    {
        send(str[i]);
    }
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(const char* str, int size)
{
    for (int i = 0; i < size; ++i)
    {
        send(str[i]);
    }
}

// template <USARTS UsartNumber>
// void USART<UsartNumber>::sendMessage(u8* payload, u8 size)
// {
//     send(size);
//     send(payload, size);
//     waitForAck(10);
// }

// template <USARTS UsartNumber>
// u8 USART<UsartNumber>::getMessage(u8* buffer)
// {
//     Logger logger("USART");
//     u8 msgSize = 1;
//     int index = 0;
//     bool receivedSize = false;
//     while (index < msgSize)
//     {
//         if (getBuffer().size())
//         {
//             if (!receivedSize)
//             {
//                 msgSize = getBuffer().getByte();
//                 logger << Level::INFO << "Received size: " << msgSize << "\n";
//                 logger << Level::INFO << "Data: ";
//                 receivedSize = true;
//             }
//             else
//             {
//                 buffer[index++] = getBuffer().getByte();
//                 logger << buffer[index - 1];
//             }
//         }
//     }
//     logger << " \n";
//     return msgSize;
// }

template <USARTS UsartNumber>
USART<UsartNumber>::USART()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
}

template <USARTS UsartNumber>
bool USART<UsartNumber>::initialized()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
    return false;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::init()
{
    USART_DeInit(USARTx_);
    InitClocks();
    GPIOInit(gpioPinTx_, gpioPinSourceTx_, gpioAF_, gpioPortTx_);
    GPIOInit(gpioPinRx_, gpioPinSourceRx_, gpioAF_, gpioPortRx_);
    NVICInit();
    USARTInit();
}

template <USARTS UsartNumber>
void USART<UsartNumber>::GPIOInit(u16 pin, u16 pinSource, u16 afUsart, GPIO_TypeDef* port)
{
    GPIO_InitTypeDef gpioInit;

    GPIO_PinAFConfig(port, pinSource, afUsart);

    gpioInit.GPIO_Pin = pin;
    gpioInit.GPIO_Mode = GPIO_Mode_AF;
    gpioInit.GPIO_OType = GPIO_OType_PP;
    gpioInit.GPIO_Speed = GPIO_Low_Speed;
    gpioInit.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(port, &gpioInit);
}

uint8_t getSubPriority(USART_TypeDef* USARTx)
{
    if (USARTx == USART1)
        return 0;
    if (USARTx == USART2)
        return 1;
    if (USARTx == USART3)
        return 2;
    return 0;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::NVICInit()
{
    NVIC_InitTypeDef init;
    init.NVIC_IRQChannel = usartIrqn_;
    init.NVIC_IRQChannelCmd = ENABLE;
    init.NVIC_IRQChannelPreemptionPriority = 6;
    init.NVIC_IRQChannelSubPriority = getSubPriority(USARTx_);
    NVIC_Init(&init);
}

template <USARTS UsartNumber>
void USART<UsartNumber>::USARTInit()
{
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 128000;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USARTx_, &USART_InitStruct);
    USART_ITConfig(USARTx_, USART_IT_RXNE, ENABLE);
    USART_Cmd(USARTx_, ENABLE);
}

template <USARTS UsartNumber>
void USART<UsartNumber>::InitClocks()
{
    static_assert(sizeof(UsartNumber) == 0, "Method needs to be specialized");
}

template <USARTS UsartNumber>
void USART<UsartNumber>::wait()
{
    while (USART_GetFlagStatus(USARTx_, USART_FLAG_TC) == RESET)
    {
    };
}

// template <USARTS UsartNumber>
// i16 USART<UsartNumber>::findMessageInBuffer(u8 msgId, u8& msgSize)
// {
//     while (true)
//     {
//         msgSize = 1;

//         int index = 0;
//         u16 readerIndex = 0;
//         bool receivedSize = false;
//         // receive message
//         while (index < msgSize)
//         {
//             u8 value;
//             if (!buffer_.getValue(readerIndex, value))
//             {
//                 return -1;
//             }
//             if (!receivedSize)
//             {
//                 msgSize = value;
//                 receivedSize = true;
//             }
//             else
//             {
//                 if (0 == index)
//                 {
//                     if (msgId == value)
//                     {
//                         return readerIndex;
//                     }
//                 }
//                 ++index;
//             }
//             ++readerIndex;
//         }
//     }
// }

// template <USARTS UsartNumber>
// void USART<UsartNumber>::removeDataFromBuffer(i16 pos, u8 nrOfBytes)
// {
//     for (int i = 0; i < nrOfBytes; ++i)
//     {
//         buffer_.removeAt(pos);
//     }
// }

// template <USARTS UsartNumber>
// void USART<UsartNumber>::waitForAck(u32 timeout)
// {
//     Logger logger("USART");
//     u8 size = 0;
//     short int pos = -1;
//     // find ack message
//     while (pos == -1)
//     {
//         pos = findMessageInBuffer(static_cast<u8>(Messages::ACK), size);
//     }

//     // remove ack message
//     // removeDataFromBuffer(pos, size);
// }

template <USARTS UsartNumber>
bool USART<UsartNumber>::isTransmissionOngoing()
{
    return transmissionOngoing_;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::setTransmissionOngoing(bool ongoing)
{
    transmissionOngoing_ = ongoing;
}


template <USARTS UsartNumber>
void USART<UsartNumber>::receive(u8 data)
{
    buffer_.write(data);
}


template <USARTS UsartNumber>
void USART<UsartNumber>::flush()
{
    buffer_.flush();
    transmissionOngoing_ = false;
    nrOfBytesToReceive_ = 0;
}

/////////////////////////////////////////////
//     specializations for USART1_PP1
/////////////////////////////////////////////
template <>
USART<USARTS::USART1_PP1>::USART()
    : gpioPortRx_(GPIOA), gpioPortTx_(GPIOA), gpioPinRx_(GPIO_Pin_10), gpioPinTx_(GPIO_Pin_9),
      gpioPinSourceRx_(GPIO_PinSource10), gpioPinSourceTx_(GPIO_PinSource9), gpioAF_(GPIO_AF_USART1),
      usartIrqn_(USART1_IRQn), transmissionOngoing_(false)
{
    USARTx_ = USART1;
    init();
}

bool wasUsart1Initialized = false;

bool returnTrue()
{
    return true;
}

template <>
USART<USARTS::USART1_PP1>& USART<USARTS::USART1_PP1>::getUsart()
{
    static USART s1;
    wasUsart1Initialized = true;
    return s1;
}

template <>
bool USART<USARTS::USART1_PP1>::initialized()
{
    return wasUsart1Initialized;
}

template <>
void USART<USARTS::USART1_PP1>::InitClocks()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

/////////////////////////////////////////////
//     specializations for USART2_PP1
/////////////////////////////////////////////
template <>
USART<USARTS::USART2_PP1>::USART()
    : gpioPortRx_(GPIOB), gpioPortTx_(GPIOB), gpioPinRx_(GPIO_Pin_11), gpioPinTx_(GPIO_Pin_10),
      gpioPinSourceRx_(GPIO_PinSource11), gpioPinSourceTx_(GPIO_PinSource10), gpioAF_(GPIO_AF_USART3),
      usartIrqn_(USART3_IRQn), transmissionOngoing_(false)
{
    USARTx_ = USART3;
    init();
}

bool wasUsart2Initialized = false;

template <>
USART<USARTS::USART2_PP1>& USART<USARTS::USART2_PP1>::getUsart()
{
    static USART s2;
    wasUsart2Initialized = true;
    return s2;
}

template <>
bool USART<USARTS::USART2_PP1>::initialized()
{
    return wasUsart2Initialized;
}

template <>
void USART<USARTS::USART2_PP1>::InitClocks()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

template class
    USART<USARTS::USART1_PP1>;

template class
    USART<USARTS::USART2_PP1>;
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char c = USART1->DR;
        hw::USART<hw::USARTS::USART1_PP1>::getUsart().receive(c);
    }
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        char c = USART2->DR;
        hw::USART<hw::USARTS::USART2_PP1>::getUsart().receive(c);
    }
}
