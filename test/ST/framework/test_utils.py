import os
import shutil
import errno
import serial
import logging

from framework.file_log import setup_logger
from framework.message_loop import MessageLoop
from framework.run_target import run_target


class TestFramework:

    def init_framework(self):
        if os.path.exists(os.path.dirname("../../artifacts/run.log")):
            shutil.rmtree("../../artifacts")
        if not os.path.exists(os.path.dirname("../../artifacts/run.log")):
            try:
                os.makedirs(os.path.dirname("../../artifacts/run.log"))
            except OSError as err:
                if err.errno != errno.EEXIST:
                    raise
        setup_logger("TEST", True, logging.DEBUG, "../../artifacts/run.log")
        self.serial_connection = serial.Serial("/dev/ttyS11")
        self.msgLoop = MessageLoop(self.serial_connection)
        self.msgLoop.run()

        # fo.write(serialConnection.read(10))
        self.target, self.timer = run_target(5)

    def teardown(self):
        self.target.kill()
        self.timer.cancel()

    def get_connection(self):
        return self.serial_connection
