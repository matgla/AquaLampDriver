#include "hal/serial/serial.hpp"
namespace hal
{
namespace serial
{

class Serial::SerialWrapper
{
};


Serial::Serial(const std::string& port, const int baudrate)
{
}

Serial::~Serial() = default;

std::size_t Serial::isDataToRecive()
{
}

void Serial::setHandler(const ReaderCallback& readerCallback)
{
}

void Serial::write(const std::string& data)
{
}

void Serial::write(const BufferSpan& buffer)
{
}

void Serial::write(u8 byte)
{
}

void Serial::process()
{
}

Serial primarySerial(config::primarySerialPort, config::primarySerialPortBaudRate);

} // namespace serial
} // namespace hal
