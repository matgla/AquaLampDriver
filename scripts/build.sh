#!/bin/bash
echo "1. Checking ENV"
./check_env.sh
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi

echo "2. Make target"
mkdir -p ../bin
cd ../bin
make -j4 -l4
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi

echo "3. Generate binary"
make msos.bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..
