#!/bin/bash
echo "1. Checking ENV"
./check_env.sh
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi

cd ..
rm -rf bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
mkdir bin
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd bin
cmake .. -G"Unix Makefiles" -DBUILD_TARGET=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=DEBUG $1 $2
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..
