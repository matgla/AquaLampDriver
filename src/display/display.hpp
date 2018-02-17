#pragma once

#include <array>
#include <cstring>

#include <gsl/span>

#include "bsp/board.hpp"
#include "display/colors.hpp"
#include "display/font.hpp"
#include "display/images.hpp"
#include "drivers/lcd/displayDriver.hpp"
#include "hal/utils/assert.hpp"
#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace display
{

struct Vector2u
{
    u16 x;
    u16 y;
};

class Display
{
public:
    enum class Style : uint8_t
    {
        Normal,
        Negative,
        Underscore
    };
    Display(bsp::Board& board, drivers::lcd::DisplayDriver& driver, Font& font);
    void backlightOn();
    void backlightOff();
    void clear(display::Colors color);
    void setPixel(u16 x, u16 y, Colors color = Colors::BLACK, Style style = Style::Normal);
    void print(char c, Colors color = Colors::BLACK, Style style = Style::Normal);
    void print(const char* str, Colors color = Colors::BLACK, Style style = Style::Normal);
    void setCursor(u8 x, u8 y);
    void setX(u8 x);
    void setY(u8 y);
    void drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color = Colors::BLACK, Style style = Style::Normal);
    void drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color = Colors::BLACK, Style style = Style::Normal);
    void drawImage(const Image& image, u8 x, u8 y, Colors color = Colors::BLACK, Style style = Style::Normal);
    void drawImage(const Image& image, Colors color = Colors::BLACK, Style style = Style::Normal);
    void incrementCursorX(u8 offsetX, u8 offsetY);
    void incrementCursorX(u8 offsetX);
    void incrementCursorY(u8 offsetY);
    void decrementCursorX(u8 offsetX);
    void decrementCursorY(u8 offsetY);
    Colors getNegative(Colors color);

    u16 getHeight() const;
    u16 getWidth() const;

    Font& getFont();

private:
    bsp::Board board_;
    Vector2u cursorPosition_;
    logger::Logger logger_;
    drivers::lcd::DisplayDriver& driver_;
    Font& font_;
};

} // namespace display
