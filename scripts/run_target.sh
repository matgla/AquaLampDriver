#!/bin/bash
"${STM_QEMU_PATH}/bin/qemu-system-gnuarmeclipse" -nographic -board STM32-P103 -mcu STM32F103RB -verbose --verbose --verbose --semihosting-config enable=on,target=native -d unimp,guest_errors -image bin_target/msos.elf

# Maple                LeafLab Arduino-style STM32 microcontroller board (r5)
#   NUCLEO-F103RB        ST Nucleo Development Board for STM32 F1 series
#   NUCLEO-F411RE        ST Nucleo Development Board for STM32 F4 series
#   NetduinoGo           Netduino GoBus Development Board with STM32F4
#   NetduinoPlus2        Netduino Development Board with STM32F4
#   OLIMEXINO-STM32      Olimex Maple (Arduino-like) Development Board
#   STM32-E407           Olimex Development Board for STM32F407ZGT6
#   STM32-H103           Olimex Header Board for STM32F103RBT6
#   STM32-P103           Olimex Prototype Board for STM32F103RBT6
#   STM32-P107           Olimex Prototype Board for STM32F107VCT6
#   STM32F0-Discovery    ST Discovery kit for STM32F051 line
#   STM32F4-Discovery    ST Discovery kit for STM32F407/417 lines
#   STM32F429I-Discovery ST Discovery kit for STM32F429/439 lines
#   generic              Generic Cortex-M board; use -mcu to define the device
