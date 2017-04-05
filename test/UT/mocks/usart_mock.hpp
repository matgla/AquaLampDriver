#pragma once

#include "mock.hpp"

#include "stm32f4xx_usart.h"


DECLARE_MOCK_FUNCTION(ITStatus, USART_GetITStatus, USART_TypeDef*, uint16_t);
DECLARE_MOCK_FUNCTION(FlagStatus, USART_GetFlagStatus, USART_TypeDef*, uint16_t);
DECLARE_MOCK_VOID_FUNCTION(USART_SendData, USART_TypeDef*, uint16_t);

void expectSendData(char data);
void expectSendData(const char* data);
void expectSendData(u8* data, u8 size);
void expectClocksConfiguration();
void expectGpioInit();
void expectNvicInit();
void expectInitialization();
