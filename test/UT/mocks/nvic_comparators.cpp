#include <iostream>

#include "comparators.hpp"

namespace comparators {
bool isEqual(NVIC_InitTypeDef* a, NVIC_InitTypeDef* b)
{
    if (a->NVIC_IRQChannel != b->NVIC_IRQChannel) {
        std::cerr << std::to_string(a) << " != " << std::to_string(b) << std::endl;
        return false;
    }
    if (a->NVIC_IRQChannelPreemptionPriority != b->NVIC_IRQChannelPreemptionPriority) {
        std::cerr << std::to_string(a) << " != " << std::to_string(b) << std::endl;
        return false;
    }
    if (a->NVIC_IRQChannelSubPriority != b->NVIC_IRQChannelSubPriority) {
        std::cerr << std::to_string(a) << " != " << std::to_string(b) << std::endl;
        return false;
    }
    if (a->NVIC_IRQChannelCmd != b->NVIC_IRQChannelCmd) {
        std::cerr << std::to_string(a) << " != " << std::to_string(b) << std::endl;
        return false;
    }
    return true;
}
}