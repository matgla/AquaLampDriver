#!/bin/bash
CURRENT_USER=${USER}
echo "${CURRENT_USER}"
sudo socat pty,link=/dev/ttyS10 pty,link=/dev/ttyS11 &
sleep 1
sudo stty -F /dev/ttyS10 -onlcr && sudo stty -F /dev/ttyS11 -onlcr
sudo chown "${CURRENT_USER}" /dev/ttyS10 && sudo chown "${CURRENT_USER}" /dev/ttyS11
