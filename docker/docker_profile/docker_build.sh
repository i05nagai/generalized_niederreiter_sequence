#!/bin/bash

script_dir=$(cd $(dirname ${0});pwd)
cp ${script_dir}/../../scripts/travis_cmake_setup.sh travis_cmake_setup.sh
chmod 755 travis_cmake_setup.sh
docker build . -t gns/profiler:latest
