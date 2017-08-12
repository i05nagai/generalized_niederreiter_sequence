#!/bin/bash

cp ../../ci/travis_cmake_setup.sh travis_cmake_setup.sh
docker build . -t gns/valgrind:latest
