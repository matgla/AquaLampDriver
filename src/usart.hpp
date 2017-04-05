#pragma once

#include "utils.hpp"
#include <cstdint>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <system_stm32f4xx.h>

#include "readerWriterBuffer.hpp"

#define USART_WAIT(USARTx)                       \
    do                                           \
    {                                            \
        while (!((USARTx)->SR & USART_FLAG_TXE)) \
            ;                                    \
    } while (0)
#define BUFFER_SIZE 1000

void USART_GPIO_init(void);
void USART_NVIC_init(void);
void USART_init(void);
void usart_put(USART_TypeDef* USARTx, const char* str);

namespace hw
{
extern bool wasUsart1Initialized;
enum class USARTS
{
    USART1_PP1,
    USART2_PP1
};

template <USARTS UsartNumber>
class USART
{
  public:
    static USART& getUsart();
    static bool initialized();
    ReaderWriterBuffer<BUFFER_SIZE>& getBuffer();
    void send(char ch);
    void send(char* str);
    void send(u8* str, int size);
    void send(const char* str, int size);
    void sendMessage(u8* message, u8 size);
    u8 getMessage(u8* buffer);
    bool isTransmissionOngoing();
    void setTransmissionOngoing(bool ongoing);
    void receive(u8 data);
    void flush();
    void waitForAck(u32 timeout);

  private:
    USART();
    void init();
    void GPIOInit(u16 pin, u16 pinSource, u16 afUsart, GPIO_TypeDef* port);
    void NVICInit();
    void USARTInit();
    void InitClocks();
    void wait();
    i16 findMessageInBuffer(u8 msgId, u8& size);
    void removeDataFromBuffer(i16 pos, u8 nrOfBytes);


    GPIO_TypeDef* gpioPortRx_;
    GPIO_TypeDef* gpioPortTx_;
    u16 gpioPinRx_;
    u16 gpioPinTx_;
    u16 gpioPinSourceRx_;
    u16 gpioPinSourceTx_;

    u16 gpioAF_;

    u16 usartIrqn_;

    USART_TypeDef* USARTx_;
    volatile bool transmissionOngoing_;
    volatile u8 nrOfBytesToReceive_;

    ReaderWriterBuffer<BUFFER_SIZE> buffer_;
};
}

extern "C" {
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
}