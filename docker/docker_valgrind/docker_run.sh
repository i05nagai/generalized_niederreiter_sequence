#!/bin/bash

PATH_TO_REPOSITORY=$(cd $(dirname ${0})/../../;pwd)
PATH_TO_REPOSITORY_IN_DOCKER="/tmp/repository"

docker run -it \
  --rm \
  --volume ${PATH_TO_REPOSITORY}:${PATH_TO_REPOSITORY_IN_DOCKER} \
  --workdir ${PATH_TO_REPOSITORY_IN_DOCKER} \
  --env GNS_BUILD_BENCHMARKS="-DGNS_BUILD_BENCHMARKS=ON" \
  --env GNS_BUILD_EXAMPLES="-DGNS_BUILD_EXAMPLES=OFF" \
  --env GNS_BUILD_TEST_MEMORYCHECK="-DGNS_BUILD_TEST_MEMORYCHECK=ON" \
  gns/valgrind:latest \
  ${PATH_TO_REPOSITORY_IN_DOCKER}/ci/build_cmake.sh build_docker
