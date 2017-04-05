#!/bin/bash
CURRENT_USER=${USER}
echo "${CURRENT_USER}"
sudo socat PTY,link=/dev/ttyS10,raw PTY,link=/dev/ttyS11,raw &
sleep 1
sudo stty -F /dev/ttyS10 -onlcr && sudo stty -F /dev/ttyS11 -onlcr
sudo chown "${CURRENT_USER}" /dev/ttyS10 && sudo chown "${CURRENT_USER}" /dev/ttyS11