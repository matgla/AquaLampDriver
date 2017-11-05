#pragma once
#include <cstdint>

struct font
{
    uint8_t height;
    uint8_t width;
    uint8_t bufferSize;
    const uint8_t* array;
};


extern font font_5x7;