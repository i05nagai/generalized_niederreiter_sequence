#!/bin/bash -x

build_dir=$1
if [[ -z ${build_dir} ]]
then
  build_dir="build"
fi

#make dir if not exists
if [[ ! -d ${build_dir} ]]
then
  mkdir ${build_dir}
fi

ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

#cd build
cd ${build_dir}
ret=$?
if [ $ret -ne 0 ]
then
    exit $ret
fi

#cmake
cmake .. $GNS_BUILD_TEST $GNS_BUILD_TEST_MEMORYCHECK $GNS_BUILD_EXAMPLES $GNS_BUILD_BENCHMARKS
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

if [ -n "$GNS_BUILD_TEST_MEMORYCHECK" ]
then
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

