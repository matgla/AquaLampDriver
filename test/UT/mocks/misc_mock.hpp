#pragma once

#include "mock.hpp"

DECLARE_MOCK_VOID_FUNCTION(NVIC_Init, NVIC_InitTypeDef*);
DECLARE_MOCK_VOID_FUNCTION(NVIC_SetVectorTable, uint32_t, uint32_t);