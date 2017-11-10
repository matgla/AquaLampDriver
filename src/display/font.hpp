#pragma once
#include <cstdint>

namespace display
{

struct Font
{
    const uint8_t height;
    const uint8_t width;
    const uint8_t* array;
};

extern Font font_5x7;
} // namespace display
