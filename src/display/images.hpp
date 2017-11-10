#pragma once

#include <cstdint>

#include <gsl/span>

namespace display
{

struct Image
{
    uint8_t width;
    uint8_t height;
    gsl::span<const uint8_t> data;
};

namespace Images
{
extern Image bulb;
extern Image emptyTriangle;
extern Image fullTriangle;
extern Image selectIcon;
extern Image backIcon;
extern Image ArrowDown;
extern Image ArrowUp;
extern Image ChessboardMosaic;
} // namespace Images

} // namespace display
