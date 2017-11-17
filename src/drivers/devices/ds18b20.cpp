#include "drivers/devices/ds18b20.hpp"

// clang-format off

//================
//| ROM COMMANDS |
//================
#define READ_ROM     0x33
#define MATCH_ROM    0x55
#define SKIP_ROM     0xCC
#define ALARM_SEARCH 0xec

//=================
//|   FUNCTIONS   |
//=================
#define CONVERT_TEMPERATURE 0x44
#define WRITE_SCRATCHPAD    0x4e
#define READ_SCRATCHPAD     0xbe
#define COPY_SCRATCHPAD     0x48
#define RECALL_E2           0xb8
#define READ_POWER_SUPPLY   0xb4
// clang-format on

namespace drivers
{
namespace devices
{

Ds18b20::Ds18b20(bsp::Board& board)
    : bus_(board)
{
}

} // namespace devices
} // namespace drivers
