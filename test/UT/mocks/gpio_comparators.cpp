#include "comparators.hpp"

#include "stm32f4xx_gpio.h"

namespace comparators {
bool isEqual(GPIO_InitTypeDef* a, GPIO_InitTypeDef* b)
{
    if (!isEqual(a->GPIO_Pin, b->GPIO_Pin)) {
        return false;
    }
    if (!isEqual(a->GPIO_Mode, b->GPIO_Mode)) {
        return false;
    }
    if (!isEqual(a->GPIO_Speed, b->GPIO_Speed)) {
        return false;
    }
    if (!isEqual(a->GPIO_OType, b->GPIO_OType)) {
        return false;
    }
    if (!isEqual(a->GPIO_PuPd, b->GPIO_PuPd)) {
        return false;
    }

    return true;
}
}