#pragma once

#include "stm32f4xx_flash.h"

#include "mock.hpp"

DECLARE_MOCK_VOID_FUNCTION_NO_PARAMS(FLASH_Unlock);
DECLARE_MOCK_VOID_FUNCTION_NO_PARAMS(FLASH_Lock);
DECLARE_MOCK_VOID_FUNCTION(FLASH_ClearFlag, uint32_t);
DECLARE_MOCK_FUNCTION(FLASH_Status, FLASH_EraseSector, uint32_t, uint8_t);
DECLARE_MOCK_FUNCTION(FLASH_Status, FLASH_ProgramByte, uint32_t, uint8_t);
