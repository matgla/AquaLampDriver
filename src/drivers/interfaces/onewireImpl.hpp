#include "drivers/interfaces/onewire.hpp"

#include "hal/time/sleep.hpp"
#include "containers/staticVector.hpp"

namespace drivers
{
namespace interfaces
{

template <std::size_t NumberOfDevices>
OneWire<NumberOfDevices>::OneWire(bsp::Board& board)
    : board_(board)
{
}

template <std::size_t NumberOfDevices>
InterfaceStates OneWire<NumberOfDevices>::reset()
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

template <std::size_t NumberOfDevices>
void OneWire<NumberOfDevices>::write(const u8 byte)
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

template <std::size_t NumberOfDevices>
u8 OneWire<NumberOfDevices>::read()
{
    u8 byte = 0;
    for (u8 i = 0; i < sizeof(u8); ++i)
    {
        if (Bit::High == readBit())
        {
            byte |= (0x01 << i);
        }
    }
    return byte;
}

template <std::size_t NumberOfDevices>
Bit OneWire<NumberOfDevices>::readBit()
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

template <std::size_t NumberOfDevices>
void OneWire<NumberOfDevices>::writeBit(const Bit& bit)
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

template <std::size_t NumberOfDevices>
InterfaceStates OneWire<NumberOfDevices>::performAutodetection()
{
    // number of conflicts = number of devices always
    containers::StaticVector<u8, NumberOfDevices> conflictPositions;
    for (std::size_t deviceIndex = 0; deviceIndex < NumberOfDevices; ++deviceIndex)
    {
        const auto status = reset();
        u64& address      = devicesAddresses_[deviceIndex];
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
                writeBit(Bit::High);
            }
            else // got "0"
            {
                // read complementary bit
                if (Bit::Low == readBit())
                {
                    // whops, we got conflict
                    // teraz trzeba wybrać 0 czy 1, dodaje pozycje do tablicy konfliktow
                    // sprawdzam czy pozycja juz jest w tablicy konfliktow
                    // jesli jest to ostatni wpis to wybieram "1", bo poprzednim razem wzialem "0",
                    // jesli to jest nie ostatni wpis to biore "0"
                    // conflictsPositions

                    // if some conflicts are known
                    if (conflictPositions.size())
                    {
                        // and if this conflict is last on conflicts lists, this mean that we are
                        // on lowest part of searching tree
                        if (i == conflictPositions.get_last())
                        {
                            // remove last conflict
                            conflictPositions.pop_back();
                            writeBit(Bit::High);
                        }
                    }
                    writeBit(Bit::Low);
                    conflictPositions.push_back(i);
                    // ale jak skminić co
                }
                else
                {
                    writeBit(Bit::Low);
                }
            }
            address << 1;
        }
        devicesAddresses_[deviceIndex] = address;
    }
}

} // namespace drivers
} // namespace interfaces
