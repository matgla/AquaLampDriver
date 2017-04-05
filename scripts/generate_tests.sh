#!/bin/bash
cd ..
rm -rf bin_test
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
mkdir bin_test
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd bin_test
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cmake .. -G"Unix Makefiles" -DBUILD_TESTS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $1 $2
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..