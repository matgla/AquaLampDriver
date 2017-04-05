#include "handshake.hpp"
#include "deviceInfoReader.hpp"
#include "usart.hpp"

Handshake::Handshake(Logger& logger)
    : connectedToClient_(false),
      logger_(logger)
{
}

void Handshake::registerClient(const ClientInfo& clientInfo)
{
    connectedToClient_ = true;
    sendDeviceIdData();
}

void Handshake::sendDeviceIdData()
{
    DeviceInfo deviceInfo;
    deviceInfo.fd_ = static_cast<u8>(FileDescriptors::COMMUNICATION);
    deviceInfo.deviceSignature_ = deviceInfoReader::readDeviceSignature();
    deviceInfo.deviceRevision_ = deviceInfoReader::readDeviceRevision();
    deviceInfo.flashSize_ = deviceInfoReader::readFlashSize();
    deviceInfoReader::readUniqueId(deviceInfo.uniqueId_);

    logger_ << Level::INFO << "sending device info\n";
    //hw::USART<hw::USARTS::USART1_PP1>::getUsart()
    //    .sendMessage(reinterpret_cast<u8*>(&deviceInfo), sizeof(DeviceInfo));
    logger_ << Level::INFO << "Received ack\n";
}