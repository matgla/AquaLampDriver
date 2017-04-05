#pragma once

#include "mock.hpp"

DECLARE_MOCK_VOID_FUNCTION(RCC_AHB1PeriphClockCmd, uint32_t, FunctionalState);
DECLARE_MOCK_VOID_FUNCTION(RCC_APB2PeriphClockCmd, uint32_t, FunctionalState);
