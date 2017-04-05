#include "bootloader.hpp"
#include "messages.hpp"
#include "usart.hpp"
#include "usart_downloader.hpp"

BootLoader::BootLoader(Logger& logger)
    : logger_(logger),
      handshake_(logger)
{
}

BootLoader::~BootLoader()
{
}

void BootLoader::handleEvent(void* event, u8 size)
{
    Logger logger("EV_HAN\0");
    u8* payload = static_cast<u8*>(event);
    Messages id = static_cast<Messages>(payload[1]);
    switch (id)
    {
        case Messages::CLIENT_INFO:
        {
            ClientInfo info;
            logger << Level::INFO << "Handshake with size: " << size << "\n";
            memcpy(&info, event, size);
            logger << Level::INFO << "Received handshake from: " << info.name_ << "\n";
            handshake_.registerClient(info);
        }
        break;
        default:
        {
        }
    }
}

bool BootLoader::specialMode()
{
    return true; // TODO: implement based on system flags
}

void BootLoader::bootSpecialMode()
{
    u8 buffer[255];
    while (true)
    {
        u8 size = hw::USART<hw::USARTS::USART1_PP1>::getUsart().getMessage(buffer);
        logger_ << Level::INFO << "Received with size: " << size << "\n";
        handleEvent(static_cast<void*>(buffer), size);
    }
    //Handshake
}

void BootLoader::bootFW()
{
    // TODO: implement
}

void BootLoader::bootDFU()
{
    UsartDownloader dwnl(logger_);
    dwnl.waitForProvider();
    dwnl.writeToMemory();
}