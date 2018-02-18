#pragma once

#include <cstdint>

namespace gui
{
constexpr auto __KEYS_LINE_START = __LINE__;
enum Keys : uint8_t
{
    None,
    Left,
    Right,
    Down,
    Up,
    Select,
    Back
};
constexpr auto KeysSize = __LINE__ - __KEYS_LINE_START - 3;


} // namespace gui