#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0})/../../;pwd)
PATH_TO_REPOSITORY_IN_DOCKER="/tmp/repository"

docker run -it \
  --rm \
  --volume ${PATH_TO_REPOSITORY}:${PATH_TO_REPOSITORY_IN_DOCKER} \
  --workdir ${PATH_TO_REPOSITORY_IN_DOCKER} \
  --env GNS_CMAKE_BUILD_TYPE="-DCMAKE_BUILD_TYPE=Release" \
  --env GNS_BUILD_BENCHMARKS="-DGNS_BUILD_BENCHMARKS=OFF" \
  --env GNS_BUILD_WITH_PROFILE="-DGNS_BUILD_WITH_PROFILE=ON" \
  --env GNS_BUILD_EXAMPLES="-DGNS_BUILD_EXAMPLES=ON" \
  --env GNS_BUILD_TEST_MEMORYCHECK="-DGNS_BUILD_TEST_MEMORYCHECK=OFF" \
  gns/profiler:latest \
  ${PATH_TO_REPOSITORY_IN_DOCKER}/docker/docker_profile/gprof.sh build_gprof
