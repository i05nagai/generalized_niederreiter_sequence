#!/bin/bash

set -x
set -e

build_dir=$1

if [[ ! -e ${build_dir} ]]
then
  mkdir ${build_dir}
fi
cd ${build_dir}
cmake .. ${GNS_CMAKE_BUILD_TYPE} ${GNS_BUILD_BENCHMARKS} ${GNS_BUILD_WITH_PROFILE} ${GNS_BUILD_EXAMPLES} ${GNS_BUILD_TEST_MEMORYCHECK}
make

cd examples
for filename in $(ls example_* ); do
  chmod 755 ${filename}
  ./${filename}
  gprof ${filename} > gprof_${filename}
done
