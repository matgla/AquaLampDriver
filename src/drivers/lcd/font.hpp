#pragma once
#include <cstdint>

struct font
{
    uint8_t height;
    uint8_t width;
    const uint8_t* array;
};


extern font font_5x7;