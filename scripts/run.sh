#!/bin/bash
"${STM_QEMU_PATH}/bin/qemu-system-gnuarmeclipse" -nographic -board NUCLEO-F103RB -verbose --verbose --verbose --semihosting-config enable=on,target=native -d unimp,guest_errors -image $1 -serial /dev/ttyS10
