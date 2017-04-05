enum class LcpCodes
{
    ConfiqureReq = 0x01,
    ConfigureAck = 0x02,
    ConfigureNack = 0x03,
    ConfigureReject = 0x04,
    TerminateReq = 0x05,
    TerminateAck = 0x06,
    CodeReject = 0x07,
    ProtocolReject = 0x08,
    EchoRequest = 0x09,
    EchoReply = 0x0a,
    DiscardRequest = 0x0b
}

struct LcpPacket
{
    u8 code;
    u8 id;
    u16 len;
    u8* data;
};