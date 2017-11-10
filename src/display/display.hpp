#pragma once

#include <array>
#include <cstring>

#include <gsl/span>

#include "bsp/board.hpp"
#include "drivers/lcd/font.hpp"
#include "drivers/lcd/icons.hpp"
#include "hal/utils/assert.hpp"
#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace drivers
{
namespace lcd
{
    class DisplayDriver;

}
}

namespace display
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
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
class Display
{
public:
    Display(bsp::Board& board, drivers::lcd::DisplayDriver& driver, Font& font);
    void backlightOn() const;
    void backlightOff() const;
    void clear();
    void setPixel(u16 x, u16 y);
    void print(char c, Colors color = Colors::BLACK);
    void print(const char* c, Colors color = Colors::BLACK);
    void setCursor(u8 x, u8 y);
    void setX(u8 x);
    void setY(u8 y);
    void drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color = Colors::BLACK);
    void drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color = Colors::BLACK);
    void drawImage(const Image& image, u8 x, u8 y, Colors color = Colors::BLACK);
    void drawImage(const Image& image, Colors color = Colors::BLACK);
    void incrementCursorX(u8 offsetX, u8 offsetY);
    void incrementCursorX(u8 offsetX);
    void incrementCursorY(u8 offsetY);
private:
    void sendToDriver();

    bsp::Board board_;
    Vector2u cursorPosition_;
    logger::Logger logger_;
    drivers::lcd::DisplayDriver& driver_;
    Font& font_;
    std::array<Colors, DisplayHeight * DisplayWidth> buffer_;
};

// Display impl
template <std::size_t DisplayHeight, std::size_t DisplayWidth>
Display<DisplayHeight, DisplayWidth>::Display(bsp::Board& board,
    drivers::lcd::DisplayDriver& driver, Font& font)
  : board_(board), cursorPosition_{0, 0}, logger_("Display"),
    driver_(driver), font_(font)
{
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::backlightOn() const
{
    board_.lcdBacklight.on();
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::backlightOff() const
{
    board_.lcdBacklight.off();
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::clear(const Colors& color)
{
    for (int y = 0; y < DisplayHeight; ++y)
    {
        for (int x = 0; x < DisplayWidth; ++x)
        {
            setPixel(x, y, color);
        }
    }
    cursorPosition_.x = 0;
    cursorPosition_.y = 0;
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::setPixel(u16 x, u16 y, const Colors& color)
{
    if (x * y >= DisplayHeight * DisplayWidth)
    {
        logger_.error() << "Trying to set pixel outside buffer setPixel("
            << x << ", " << y << "), where display(" << DisplayWidth
            << ", " << DisplayHeight << ")!";
        return;
    }

    buffer_[x*y] = color;
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::print(char c, Colors color = Colors::BLACK)
{
    u16 charOffset = c - 32; // 32 first letter in font
    u16 charPosition = charOffset + charOffset * (usedFont.width - 1);

    const uint8_t* font_ptr = &usedFont.array[charPosition];

    if (c == 0xA)
    {
        cursorPosition_.x = 0;
        cursorPosition_.y += usedFont->height + 1;
        return;
    }

    else if (c == 0x08)
    {
        cursorPosition_.x -= (usedFont->width + 1);
        c = ' ';
    }

    int i = 0;

    for (i = cursorPosition_.x; i < usedFont.width + cursorPosition_.x; i++)
    {
        for (int j = usedFont->height; j > 0; j--)
        {
            if ((*font_ptr >> j) & 0x01)
            {
                if (i < DisplayWidth && (cursorPosition_.y + usedFont.height - j) < DisplayHeight)
                {
                    setPixel(i, cursorPosition_.y + usedFont.height - j, color);
                }
            }
        }
        ++font_ptr;
    }
    incrementCursorX(usedFont.width + 1, usedFont.height + 1);
    sendToDriver();
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::print(
    const char* c, Colors color = Colors::BLACK)
{
    for (std::size_t i = 0; i < strlen(str); i++)
    {
        print(str[i], color);
    }
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::setCursor(u8 x, u8 y)
{
    cursorPosition_.x = x;
    cursorPosition_.y = y;
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::setX(u8 x)
{
    cursorPosition_.x = x;
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::setY(u8 y)
{
    cursorPosition_.y = y;
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color = Colors::BLACK)
{
    UNUSED(color);
    if (buffer.length() < width || sizeof(buffer[0]) * 8 < height)
    {
        logger_.error() << "Buffer smaller than picture";
        logger_.error() << "buffer.length()=" << buffer.length() << ", width=" << width << ", sizeof(buffer[0])=" << sizeof(buffer[0]) << ", height=" << height;
        return;
    }

    int i = 0;
    for (int x = cursorPosition_.x; x < cursorPosition_.x + width; ++x)
    {
        for (int y = height; y > 0; --y)
        {
            if ((buffer[i] >> y) & 0x01)
            {
                if (x < DisplayWidth && (cursorPosition_.y + height - y) < DisplayHeight)
                {
                    display_.setPixel(x, cursorPosition_.y + height - y, color);
                }
            }
        }
        i++;
    }

    incrementCursorX(width, usedFont.height);
    drawScreen();
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color = Colors::BLACK)
{
    UNUSED(color);
    cursorPosition_.x = x;
    cursorPosition_.y = y;
    drawImage(buffer, width, height);
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::drawImage(const Image& image, u8 x, u8 y, Colors color = Colors::BLACK)
{
    UNUSED(color);
    drawImage(image.data, image.width, image.height);
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::drawImage(const Image& image, Colors color = Colors::BLACK)
{
    UNUSED(color);
    cursorPosition_.x = x;
    cursorPosition_.y = y;
    drawImage(image);
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::incrementCursorX(u8 offsetX, u8 offsetY)
{
    if (cursorPosition_.x + offsetX >= DisplayWidth)
    {
        cursorPosition_.y += offsetY;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.x += offsetX;
    }
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::incrementCursorX(u8 offsetX)
{
    incrementCursorX(offsetX, usedFont.height);
}

template <std::size_t DisplayHeight, std::size_t DisplayWidth>
void Display<DisplayHeight, DisplayWidth>::incrementCursorY(u8 offsetY)
{
    if (cursorPosition_.y + offsetY >= DisplayHeight)
    {
        cursorPosition_.y = offsetY;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.y += offsetY;
    }
}

} // namespace display
