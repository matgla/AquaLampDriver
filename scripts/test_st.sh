#!/bin/bash
cd ../test/ST
behave
RC="$?"
if [ $RC -ne 0 ]; then
    exit $RC
fi
cd ../..