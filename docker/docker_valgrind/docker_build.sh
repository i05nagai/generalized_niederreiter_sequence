#!/bin/bash

cp ../../scripts/travis_cmake_setup.sh travis_cmake_setup.sh
chmod 755 travis_cmake_setup.sh
docker build . -t gns/valgrind:latest
