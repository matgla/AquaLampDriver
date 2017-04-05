from enum import Enum
from struct import pack, unpack


class EventType(Enum):
    ACK = 0x06
    SW_DWN_REQ = 0x0a
    CLIENT_INFO = 0x0b


class Ack:

    def __init__(self):
        self.eventId = EventType.ACK

    def serialize(self):
        serialized = pack('<B', self.eventId.value)
        return serialized


class ClientInfo:

    def __init__(self, fd, name):
        self.fd = fd
        self.id = EventType.CLIENT_INFO.value
        if len(name) >= 10:
            name = name[0:10]
        self.name = name

    def serialize(self):
        pack_format = "<BBB" + str(len(self.name)) + "s"
        serialized = pack(pack_format, len(
            self.name) + 2, self.fd, self.id, self.name)
        return serialized
