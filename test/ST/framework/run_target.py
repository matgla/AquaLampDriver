from subprocess import Popen, PIPE
from functools import partial
from threading import Timer
from time import sleep
from signal import SIGINT
from os import kill
import os

#fo = open("target.log", "w")


def kill_target(program):
    program.kill()


def run_target(timeout):
    stdout_file = "../../artifacts/stdout.log"
    stderr_file = "../../artifacts/stderr.log"
    if not os.path.exists(os.path.dirname(stdout_file)):
        try:
            os.makedirs(os.path.dirname(stdout_file))
        except OSError as err:
            # if err.errno != errno.EEXIST: TODO: fix it
            #    raise
            print "jakis error"
    with open(stdout_file, "wb") as out, open(stderr_file, "wb") as err:
        # fo.write(os.environ["STM_QEMU_PATH"] +
        #         "/bin/qemu-system-gnuarmeclipse")
        pipes = Popen([os.environ["STM_QEMU_PATH"] + "/bin/qemu-system-gnuarmeclipse", "-nographic", "-board", "STM32F4-Discovery", "-verbose", "--verbose", "--verbose", "--semihosting-config",
                       "enable=on,target=native", "-d", "unimp,guest_errors", "-image", "../../bin/stm32BootLoader.bin", "-serial", "/dev/ttyS10"], stdout=out, stderr=err, stdin=PIPE)
    t = Timer(timeout, partial(kill_target, pipes))
    t.start()  # after 30 seconds, "hello, world" will be printed
    return pipes, t
