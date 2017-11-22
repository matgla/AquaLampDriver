#pragma once

#include "bsp/board.hpp"
#include "drivers/interfaces/onewire.hpp"
#include "hal/time/sleep.hpp"

#include "logger/logger.hpp"

//=================
//|   FUNCTIONS   |
//=================
constexpr u8 CONVERT_TEMPERATURE = 0x44;
constexpr u8 WRITE_SCRATCHPAD    = 0x4e;
constexpr u8 READ_SCRATCHPAD     = 0xbe;
constexpr u8 COPY_SCRATCHPAD     = 0x48;
constexpr u8 RECALL_E2           = 0xb8;
constexpr u8 READ_POWER_SUPPLY   = 0xb4;

namespace drivers
{
namespace devices
{

template <std::size_t NumberOfDevices>
class Ds18b20
{
public:
    Ds18b20(bsp::Board& board)
        : bus_(board),
          logger_("Ds18b20")
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
        hal::time::msleep(800);

        bus_.initTranssmisionWithDevice(deviceNumber);
        bus_.write(READ_SCRATCHPAD);
        temperatureL = bus_.read();
        temperatureH = bus_.read();

        bus_.reset();
        return static_cast<float>(temperatureL + (temperatureH << 8)) / 16;
    }

private:
    interfaces::OneWire<NumberOfDevices> bus_;
    logger::Logger logger_;
};

} // namespace devices
} // namespace drivers
