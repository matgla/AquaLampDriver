#pragma once

#include "bsp/board.hpp"
#include "drivers/interfaces/onewire.hpp"
#include "hal/time/sleep.hpp"

// clang-format off



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

template <std::size_t NumberOfDevices>
class Ds18b20
{
public:
    Ds18b20(bsp::Board& board)
        : bus_(board)
    {
        bus_.performAutodetection();
    }

    float readTemperature(u8 deviceNumber)
    {
        u8 temperatureH = 0;
        u8 temperatureL = 0;
        HAL_ASSERT_MSG(deviceNumber < NumberOfDevices, "Trying to read from not existing device");
        bus_.initTranssmisionWithDevice(deviceNumber);
        bus_.write(CONVERT_TEMPERATURE);
        hal::time::msleep(750);
        bus_.initTranssmisionWithDevice(deviceNumber);
        bus_.write(READ_SCRATCHPAD);
        temperatureL = bus_.read();
        temperatureH = bus_.read();

        return static_cast<float>(temperatureL + (temperatureH << 8)) / 16;
    }

private:
    interfaces::OneWire<NumberOfDevices> bus_;
};

} // namespace devices
} // namespace drivers
