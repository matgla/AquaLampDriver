#pragma once

#define DISPLAY_HEIGHT 48
#define DISPLAY_WIDTH 84

#include <gsl/span>

#include "logger/logger.hpp"
#include "utils/types.hpp"

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
    void clear(Colors color);
    void setPixel(u8 x, u8 y, Colors color);
    void print(char c, Vector2u position);
    void print(char c, u16 x, u16 y, Colors color = Colors::BLACK);
    void print(char c, Colors color = Colors::BLACK);
    void print(const char* c, Colors color = Colors::BLACK);
    void setCursor(u8 x, u8 y);
    void setX(u8 x);
    void setY(u8 y);
    void drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color = Colors::BLACK);
    void drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color = Colors::BLACK);

private:
    void incrementCursorX(u8 offsetX, u8 offsetY);
    void incrementCursorY(u8 offsetY);

    Vector2u cursorPosition_;
    logger::Logger logger_;
};

} // namespace lcd
} // namespace drivers
