#pragma once

#include "mock.hpp"

DECLARE_MOCK_VOID_FUNCTION(GPIO_PinAFConfig, GPIO_TypeDef*, uint16_t, uint8_t);
DECLARE_MOCK_VOID_FUNCTION(GPIO_Init, GPIO_TypeDef*, GPIO_InitTypeDef*);