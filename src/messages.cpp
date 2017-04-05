#include "messages.hpp"

MessageHeader::MessageHeader(u8 fd)
    : fd_(fd)
{
}

Ack::Ack()
{
    id_ = static_cast<u8>(Messages::ACK);
}

RequestDownload::RequestDownload()
{
    id_ = static_cast<u8>(Messages::SW_DWN_REQ);
}

ClientInfo::ClientInfo()
{
    id_ = static_cast<u8>(Messages::CLIENT_INFO);
}