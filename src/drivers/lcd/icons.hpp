#pragma once

#include <cstdint>

#include <gsl/span>

namespace drivers
{
namespace lcd
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
} // namespace Images

} // namespace lcd
} // namespace drivers
