FROM ubuntu:14.04

RUN apt-get -y update
RUN apt-get -y install valgrind
RUN apt-get -y install build-essential
RUN apt-get -y install curl
ADD travis_cmake_setup.sh /tmp/
RUN /tmp/travis_cmake_setup.sh
