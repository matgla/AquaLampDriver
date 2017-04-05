#include "gtest/gtest.h"

#include "stm32f4xx_rcc.h"

#include "rcc_mock.hpp"

MOCK_VOID_FUNCTION(RCC_AHB1PeriphClockCmd, uint32_t, FunctionalState);
MOCK_VOID_FUNCTION(RCC_APB2PeriphClockCmd, uint32_t, FunctionalState);