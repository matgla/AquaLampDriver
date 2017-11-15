#pragma once
#include <cstdint>

namespace display
{

struct Font
{
    const uint16_t height;
    const uint16_t width;
    const uint8_t* array;
};

extern Font font_5x7;
} // namespace display
