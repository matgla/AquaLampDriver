import struct

class FileDescriptors:
    STDIO = 0
    STDOUT = 1
    STDERR = 2
    LOGGER = 3
    

class L1Message:
    __init__(self, serial):
        self.serial = serial
    
    def send(fd, payload):
        data_to_send = struct.pack("BBP")
        serial.write(fd)
        