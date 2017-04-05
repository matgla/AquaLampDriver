#include "flash_mock.hpp"

MOCK_VOID_FUNCTION_NO_PARAMS(FLASH_Unlock);
MOCK_VOID_FUNCTION_NO_PARAMS(FLASH_Lock);
MOCK_VOID_FUNCTION(FLASH_ClearFlag, uint32_t);
MOCK_FUNCTION(FLASH_Status, FLASH_EraseSector, uint32_t, uint8_t);
MOCK_FUNCTION(FLASH_Status, FLASH_ProgramByte, uint32_t, uint8_t);