#!/bin/bash

echo "Checking if all environment variables exist"

if [ -z $ARM_TOOLCHAIN ]; then
    echo "ARM_TOOLCHAIN environment variable doesn't exist"
    exit 1
fi

if [ -z $STM32_LIBRARY_ROOT_DIR ]; then
    echo "STM32_LIBRARY_ROOT_DIR environment variable doesn't exist"
    exit 1
fi
