#include "stm32f4xx_usart.h"

#include <vector>

#include "gpio_mock.hpp"
#include "misc_mock.hpp"
#include "mock.hpp"
#include "rcc_mock.hpp"


USART_TypeDef usart1;

MOCK_FUNCTION(ITStatus, USART_GetITStatus, USART_TypeDef*, uint16_t);
MOCK_FUNCTION(FlagStatus, USART_GetFlagStatus, USART_TypeDef*, uint16_t);
MOCK_VOID_FUNCTION(USART_SendData, USART_TypeDef*, uint16_t);

void USART_DeInit(USART_TypeDef* USARTx)
{
}

void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
}

void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
}

void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
}

void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
}

void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{
}

void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
}

void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
}

void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp)
{
}

void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
}

void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SendBreak(USART_TypeDef* USARTx)
{
}

void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{
}

void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode)
{
}

void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
}

void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
}

void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
}

void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
}


void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
}


void expectSendData(char data)
{
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
    EXPECT_CALL(USART_SendData, USART1, data);
    EXPECT_CALL(USART_GetFlagStatus, USART1, USART_FLAG_TC).willReturn(SET);
}

void expectSendData(const char* data)
{
    for (int i = 0; i < strlen(data); ++i)
    {
        expectSendData(data[i]);
    }
}

void expectSendData(u8* data, u8 size)
{
    for (int i = 0; i < size; ++i)
    {
        expectSendData(data[i]);
    }
}


void expectClocksConfiguration()
{
    EXPECT_CALL(RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA, ENABLE);
    EXPECT_CALL(RCC_APB2PeriphClockCmd, RCC_APB2Periph_USART1, ENABLE);
}

GPIO_InitTypeDef expectedGpioInitialization;
GPIO_InitTypeDef expectedGpio2Initialization;
NVIC_InitTypeDef init;

void expectGpioInit()
{
    EXPECT_CALL(GPIO_PinAFConfig, GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

    expectedGpioInitialization.GPIO_Pin = GPIO_Pin_9;
    expectedGpioInitialization.GPIO_Mode = GPIO_Mode_AF;
    expectedGpioInitialization.GPIO_OType = GPIO_OType_PP;
    expectedGpioInitialization.GPIO_Speed = GPIO_Low_Speed;
    expectedGpioInitialization.GPIO_PuPd = GPIO_PuPd_UP;
    EXPECT_CALL(GPIO_Init, GPIOA, &expectedGpioInitialization);

    expectedGpio2Initialization.GPIO_Pin = GPIO_Pin_10;
    expectedGpio2Initialization.GPIO_Mode = GPIO_Mode_AF;
    expectedGpio2Initialization.GPIO_OType = GPIO_OType_PP;
    expectedGpio2Initialization.GPIO_Speed = GPIO_Low_Speed;
    expectedGpio2Initialization.GPIO_PuPd = GPIO_PuPd_UP;

    EXPECT_CALL(GPIO_PinAFConfig, GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    EXPECT_CALL(GPIO_Init, GPIOA, &expectedGpio2Initialization);
}

void expectNvicInit()
{
    init.NVIC_IRQChannel = USART1_IRQn;
    init.NVIC_IRQChannelCmd = ENABLE;
    init.NVIC_IRQChannelPreemptionPriority = 6;
    init.NVIC_IRQChannelSubPriority = 0;

    EXPECT_CALL(NVIC_Init, &init);
}

void expectInitialization()
{
    expectClocksConfiguration();
    expectGpioInit();
    expectNvicInit();
}