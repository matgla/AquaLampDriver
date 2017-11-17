#include "drivers/interfaces/onewire.hpp"

#include "hal/time/sleep.hpp"

namespace drivers
{
namespace interfaces
{

OneWire::OneWire(bsp::Board& board)
    : board_(board)
{
}

InterfaceStates OneWire::reset()
{
    board_.oneWire.setAsOutput();
    board_.oneWire.setState(bsp::BusState::Low);
    hal::time::usleep(500);
    board_.oneWire.setState(bsp::BusState::High);
    board_.oneWire.setAsInput();
    hal::time::usleep(70);
    // device detected
    if (bsp::BusState::Low == board_.oneWire.getState())
    {
        hal::time::usleep(500);
        if (bsp::BusState::High == board_.oneWire.getState())
        {
            return InterfaceStates::Detected;
        }
        // bus must be in high state now, but is not
        return InterfaceStates::BusError;
    }
    // any device answered
    return InterfaceStates::NotDetected;
}

void OneWire::write(const u8 byte)
{
    for (u8 i = 0; i < sizeof(u8); ++i)
    {
        if (byte & (0x01 << i))
        {
            writeBit(Bit::High);
        }
        else
        {
            writeBit(Bit::Low);
        }
    }
}

u8 OneWire::read()
{
    u8 byte = 0;
    for (u8 i = 0; i < sizeof(u8); ++i)
    {
        if (Bit::High == readBit())
        {
            byte |= (0x01 << i);
        }
    }
}

Bit OneWire::readBit()
{
    Bit bit = Bit::Low;
    board_.oneWire.setAsOutput();
    board_.oneWire.setState(bsp::BusState::Low);
    hal::time::usleep(2);
    board_.oneWire.setState(bsp::BusState::High);
    board_.oneWire.setAsInput();
    hal::time::usleep(7);
    if (bsp::BusState::High == board_.oneWire.getState())
    {
        bit = Bit::High;
    }
    hal::time::usleep(70);
    return bit;
}

void OneWire::writeBit(const Bit& bit)
{
    board_.oneWire.setAsOutput();
    board_.oneWire.setState(bsp::BusState::Low);
    if (Bit::High == bit)
    {
        // transmit "1"
        hal::time::usleep(15);
        board_.oneWire.setState(bsp::BusState::High);
        board_.oneWire.setAsInput();
        hal::time::usleep(70);
    }
    else
    {
        // transmit "0"
        hal::time::usleep(70);
        board_.oneWire.setState(bsp::BusState::High);
        board_.oneWire.setAsInput();
        hal::time::usleep(15);
    }
}

InterfaceStates OneWire::performAutodetection()
{
    for (std::size_t deviceIndex = 0; deviceIndex < NumberOfDevices; ++deviceIndex)
    {
        const auto status = bus_.reset();
        u64& address      = devicesAddresses_[deviceIndex_];
        static_assert(sizeof(u64) >= 8, "Address variable must be 8 byte minimum");
        if (InterfaceStates::Detected != status)
        {
            return status;
        }

        write(SEARCH_ROM);

        for (u8 i = 0; i < sizeof(u64); ++i)
        {
            // read bit
            if (Bit::High == readBit())
            {
                // read complementary bit
                if (Bit::High == readBit())
                {
                    return InterfaceStates::NoDevicesOnBus;
                }
                address |= 0x01;
                writeBit(Bit::High)
            }
            else // got "0"
            {
                // read complementary bit
                if (Bit::Low == readBit())
                {
                    // whops, we got conflict
                    // teraz trzeba wybrać 0 czy 1
                    writeBit(Bit::Low);
                    // ale jak skminić co
                }
                else
                {
                    writeBit(Bit::Low);
                }
            }
            address << 1;
        }
    }
}

} // namespace drivers
} // namespace interfaces
