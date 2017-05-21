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
cmake .. $GF_BUILD_TEST $GF_BUILD_TEST_MEMORYCHECK $GF_BUILD_EXAMPLES $GF_BUILD_BENCHMARKS 
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

if [ -n "$GF_BUILD_TEST_MEMORYCHECK" ]
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
fi

exit 0

