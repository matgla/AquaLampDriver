import threading
import time
import os
import errno
import binascii
from messages import messages
from logging import getLogger

logger = getLogger("TEST")


class MessageLoop:

    def __init__(self, serial_connection):
        self.serial = serial_connection
        self.log_file_name = "../../artifacts/target.log"

    def log(self, bytearray):
        with open(self.log_file_name, "a") as file:
            file.write(bytearray.encode("utf-8"))

    def run(self):
        try:
            self.runner_thread = threading.Thread(
                target=self.loop)
            self.runner_thread.setDaemon(True)
            logger.info("Created runner thread.")
            self.runner_thread.start()
            logger.info("Runner started.")

        except Exception as err:
            logger.error(
                "Can't start thread for message handling" + str(err))
            raise

    def loop(self):
        try:
            while True:
                size = 0
                while size == 0:
                    while self.serial.in_waiting == 0:
                        pass
                    size = ord(self.serial.read(1))
                received_bytes = 0
                payload = bytearray()
                strb = ""
                while received_bytes < size:
                    if self.serial.in_waiting != 0:
                        byte = ord(self.serial.read(1))
                        strb = strb + " " + str(byte)
                        payload.append(byte)
                        received_bytes = received_bytes + 1
                logger.info("Payload[0] = " + str(payload[0]) + " p[1]: " + str(payload[1])
                            + " when size: " + str(size) + " len size: " + str(len(payload)) + " payload: " + binascii.hexlify(payload))
                if payload[0] == 0:  # log
                    self.log(payload[1:].decode())
                elif len(payload) == 1 and size == 1 and payload[0] == messages.EventType.ACK.value:
                    logger.info("received ack")
                
                logger.info("sending ack")
                msg = bytearray()
                msg.append(0x01)
                msg.append(messages.EventType.ACK.value)
                self.serial.write(msg)
        except Exception as err:
            logger.error("Error in loop: " + str(err))
            raise
