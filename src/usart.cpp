#include "usart.hpp"
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
ReaderWriterBuffer<BUFFER_SIZE>& USART<UsartNumber>::getBuffer()
{
    return this->buffer_;
}

template <USARTS UsartNumber>
void USART<UsartNumber>::send(char ch)
{
    // wait();
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

template <USARTS UsartNumber>
u32 USART<UsartNumber>::size()
{
    return this->buffer_.size();
}

template <USARTS UsartNumber>
u8 USART<UsartNumber>::read()
{
    return this->buffer_.getByte();
}

template <USARTS UsartNumber>
void USART<UsartNumber>::init()
{
    USART_DeInit(USARTx_);
    InitClocks();
    GPIOInit(gpioPinTx_, gpioPortTx_);
    GPIOInit(gpioPinRx_, gpioPortRx_);
    NVICInit();
    USARTInit();
}

template <USARTS UsartNumber>
void USART<UsartNumber>::GPIOInit(u16 pin, GPIO_TypeDef* port)
{
    GPIO_InitTypeDef gpioInit;

    // GPIO_PinAFConfig(port, pinSource, afUsart);

    gpioInit.GPIO_Pin = gpioPinRx_;
    gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING; // GPIO_Mode_AF stm32f4xx
    //gpioInit.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(port, &gpioInit);

    gpioInit.GPIO_Pin = gpioPinTx_;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
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
void USART<UsartNumber>::wait()
{
    while (USART_GetFlagStatus(USARTx_, USART_FLAG_TC) == RESET)
    {
    }
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
      usartIrqn_(USART1_IRQn), transmissionOngoing_(false)
{
    USARTx_ = USART1;
    init();
}

template <>
USART<USARTS::USART2_PP1>::USART()
    : gpioPortRx_(GPIOA), gpioPortTx_(GPIOA), gpioPinRx_(GPIO_Pin_3), gpioPinTx_(GPIO_Pin_2),
      usartIrqn_(USART2_IRQn), transmissionOngoing_(false)
{
    USARTx_ = USART2;
    init();
    send(' ');
}

bool wasUsart1Initialized = false;
bool wasUsart2Initialized = false;

bool returnTrue()
{
    return true;
}

template <>
USART<USARTS::USART1_PP1>& USART<USARTS::USART1_PP1>::getUsart()
{
    // static USART s1;
    // wasUsart1Initialized = true;
    //  return s1;
}

template <>
USART<USARTS::USART2_PP1>& USART<USARTS::USART2_PP1>::getUsart()
{
    static USART s2;
    wasUsart2Initialized = true;
    return s2;
}


template <>
bool USART<USARTS::USART1_PP1>::initialized()
{
    return wasUsart1Initialized;
}

template <>
bool USART<USARTS::USART2_PP1>::initialized()
{
    return wasUsart2Initialized;
}

template <>
void USART<USARTS::USART1_PP1>::InitClocks()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
}

template <>
void USART<USARTS::USART2_PP1>::InitClocks()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

template class USART<USARTS::USART2_PP1>;


extern "C" {
void USART2_IRQHandler(void);
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        char c = USART2->DR;
        hw::USART<hw::USARTS::USART2_PP1>::getUsart().send(c);
        hw::USART<hw::USARTS::USART2_PP1>::getUsart().receive(c);
    }
}


} // namespace hw
