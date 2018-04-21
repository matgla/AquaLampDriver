#include "display/display.hpp"

namespace display
{

Display::Display(bsp::Board& board,
                 drivers::lcd::DisplayDriver& driver, Font& font)
    : board_(board), cursorPosition_{0, 0}, logger_("Display"),
      driver_(driver), font_(font)
{
}

void Display::backlightOn()
{
    board_.lcdBacklight.on();
}

void Display::backlightOff()
{
    board_.lcdBacklight.off();
}

void Display::clear(Colors color)
{
    for (int y = 0; y < driver_.getHeight(); ++y)
    {
        for (int x = 0; x < driver_.getWidth(); ++x)
        {
            driver_.setPixel(x, y, color);
        }
    }
    cursorPosition_.x = 0;
    cursorPosition_.y = 0;

    driver_.display();
}

void Display::setPixel(u16 x, u16 y, Colors color)
{
    driver_.setPixel(x, y, color);
}

void Display::print(char c, Colors color)
{
    if (c == 0xA)
    {
        cursorPosition_.x = 0;
        cursorPosition_.y += font_.height + 1;
        return;
    }

    else if (c == 0x08)
    {
        cursorPosition_.x -= (font_.width + 1);
        c = ' ';
    }

    if (c < 32)
        return;

    u16 charOffset = static_cast<u16>(c - 32); // 32 first letter in font
    u16 charPosition = charOffset * font_.width;
    const uint8_t* font_ptr = &font_.array[charPosition];

    int i = 0;
    for (i = cursorPosition_.x; i < font_.width + cursorPosition_.x; i++)
    {
        for (u16 j = font_.height; j > 0; j--)
        {
            if ((*font_ptr >> j) & 0x01)
            {
                if (i < driver_.getWidth() && (cursorPosition_.y + font_.height - j) < driver_.getHeight())
                {
                    driver_.setPixel(i, cursorPosition_.y + font_.height - j, color);
                }
            }
        }
        ++font_ptr;
    }
    incrementCursorX(font_.width + 1, font_.height + 1);
    driver_.display();
}


void Display::print(const char* str, Colors color)
{
    for (std::size_t i = 0; i < strlen(str); i++)
    {
        print(str[i], color);
    }
}

void Display::setCursor(u8 x, u8 y)
{
    cursorPosition_.x = x;
    cursorPosition_.y = y;
}

void Display::setX(u8 x)
{
    cursorPosition_.x = x;
}

void Display::setY(u8 y)
{
    cursorPosition_.y = y;
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color)
{
    UNUSED(color);
    if (buffer.size() < width || sizeof(buffer[0]) * 8 < height)
    {
        logger_.error() << "Buffer smaller than picture";
        logger_.error() << "buffer.size()=" << buffer.size() << ", width=" << width << ", sizeof(buffer[0])=" << sizeof(buffer[0]) << ", height=" << height;
        return;
    }

    int i = 0;
    for (int x = cursorPosition_.x; x < cursorPosition_.x + width; ++x)
    {
        for (int y = height; y > 0; --y)
        {
            if ((buffer[i] >> y) & 0x01)
            {
                if (x < driver_.getWidth() && (cursorPosition_.y + height - y) < driver_.getHeight())
                {
                    driver_.setPixel(x, cursorPosition_.y + height - y, color);
                }
            }
        }
        i++;
    }

    incrementCursorX(width, font_.height);
    driver_.display();
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color)
{
    UNUSED(color);
    cursorPosition_.x = x;
    cursorPosition_.y = y;
    drawImage(buffer, width, height);
}

void Display::drawImage(const Image& image, u8 x, u8 y, Colors color)
{
    UNUSED(color);
    cursorPosition_.x = x;
    cursorPosition_.y = y;
    drawImage(image);
}


void Display::drawImage(const Image& image, Colors color)
{
    UNUSED(color);
    drawImage(image.data, image.width, image.height);
}

void Display::incrementCursorX(u8 offsetX, u8 offsetY)
{
    if (cursorPosition_.x + offsetX >= driver_.getWidth())
    {
        cursorPosition_.y += offsetY;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.x += offsetX;
    }
}

void Display::incrementCursorX(u8 offsetX)
{
    incrementCursorX(offsetX, font_.height);
}

void Display::incrementCursorY(u8 offsetY)
{
    if (cursorPosition_.y + offsetY >= driver_.getHeight())
    {
        cursorPosition_.y = offsetY;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.y += offsetY;
    }
}

u16 Display::getHeight() const
{
    return driver_.getHeight();
}

u16 Display::getWidth() const
{
    return driver_.getWidth();
}

Font& Display::getFont()
{
    return font_;
}

} // namespace display