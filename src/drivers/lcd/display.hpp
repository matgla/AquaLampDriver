#pragma once

#define DISPLAY_HEIGHT 48
#define DISPLAY_WIDTH 84

#include "utils/types.hpp"

#include "logger/logger.hpp"

namespace drivers
{
namespace lcd
{

enum class Colors
{
    BLACK,
    WHITE,
    OFF
};

struct Vector2u
{
    u16 x;
    u16 y;
};

class Display
{
public:
    Display();
    void clear(Colors color) const;
    void setPixel(u8 x, u8 y, Colors color);
    void print(char c, Vector2u position);
    void print(char c, u16 x, u16 y, Colors color = Colors::BLACK);
    void print(char c, Colors color = Colors::BLACK);
    void print(const char* c, Colors color = Colors::BLACK);

private:
    Vector2u cursorPosition_;
    Vector2u cursorOffset_;
    logger::Logger logger_;
};

} // namespace lcd
} // namespace drivers
