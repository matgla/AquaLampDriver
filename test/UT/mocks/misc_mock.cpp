#include "misc_mock.hpp"

MOCK_VOID_FUNCTION(NVIC_Init, NVIC_InitTypeDef*);
MOCK_VOID_FUNCTION(NVIC_SetVectorTable, uint32_t, uint32_t);