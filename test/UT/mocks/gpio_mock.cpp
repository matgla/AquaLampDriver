#include "stm32f4xx_gpio.h"

#include "gpio_mock.hpp"

MOCK_VOID_FUNCTION(GPIO_PinAFConfig, GPIO_TypeDef*, uint16_t, uint8_t);

MOCK_VOID_FUNCTION(GPIO_Init, GPIO_TypeDef*, GPIO_InitTypeDef*);