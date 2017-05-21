#!/bin/bash -x

#make dir
mkdir build
ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

#cd build
cd build
ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

#cmake
cmake ..
ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

#make
make
ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

#make test
ctest --verbose
ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

ctest -T memcheck --verbose | tee memcheck.log

ret=${PIPESTATUS[0]}
if [ $ret -ne 0 ]
then
    exit $ret
fi
cat memcheck.log | grep "Memory Leak" > /dev/null
ret=$?
if [ $ret -eq 0 ]
then
    exit 1
fi

exit 0

