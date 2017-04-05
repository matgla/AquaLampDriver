#!/bin/bash
echo "1. Checking ENV"
./check_env.sh
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi

echo "2. Make target"
cd ../bin
make -j4 -l4
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi

echo "3. Generate binary"
make stm32BootLoader.bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..