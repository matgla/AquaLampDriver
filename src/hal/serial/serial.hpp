#pragma once

#include <memory>
#include <string>
#include <type_traits>

#include "config.hpp"
#include "types.hpp"

namespace hal
{
namespace serial
{

class Serial // : public dispatcher::IDataReceiver
{
  public:
    explicit Serial(const std::string& port, int baudrate = 115200);
    ~Serial();
    Serial(const Serial&) = delete;
    Serial(const Serial&&) = delete;
    Serial& operator=(const Serial&& other) = delete;
    Serial& operator=(const Serial& other) = delete;

    void write(const std::string& data);
    void write(const BufferSpan& buffer);
    void write(u8 byte);

    void setHandler(const ReaderCallback& readerCallback);

    std::size_t isDataToRecive();
    void process();

  protected:
    class SerialWrapper;

    ReaderCallback readerCallback_;
    std::unique_ptr<SerialWrapper> serialWrapper_;
};

extern Serial primarySerial; //config::primarySerialPort, config::primarySerialPortBaudRate);

} // namespace serial
} // namespace hal
