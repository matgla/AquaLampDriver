#!/bin/bash
cd ../bin_test
rm -rf test/UT/bootloaderUTs
make -j2
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi

test/UT/bootloaderUTs

RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ..
