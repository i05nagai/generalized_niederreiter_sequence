[![Build Status](https://travis-ci.org/i05nagai/generalized_niederreiter_sequence.svg?branch=master)](https://travis-ci.org/i05nagai/generalized_niederreiter_sequence)
[![Coverage Status](https://coveralls.io/repos/github/i05nagai/generalized_niederreiter_sequence/badge.svg?branch=introduce-coverage-report)](https://coveralls.io/github/i05nagai/generalized_niederreiter_sequence?branch=introduce-coverage-report)

## Overviews
Generate generalized niederreiter sequence based on [Digital Nets and Sequences by Josef Dick](https://www.cambridge.org/core/books/digital-nets-and-sequences/8EB7ECB56318388BF9FA3504801D2A59).
The below picture illustrate sobol sequences and pseudo random sequence in two dimension.

![image](https://user-images.githubusercontent.com/5404587/30174873-7a9de8ae-9437-11e7-9609-708fff966a6d.png)

## Documents
* [API documents](https://i05nagai.github.io/generalized_niederreiter_sequence/build/)

## Build

```
git clone https://github.com/i05nagai/generalized_niederreiter_sequence.git
cd generalized_niederreiter_sequence
git submodule init
git submodule update
```

Simply build static lib

```shell
mkdir build
cd build
cmake ..
make
```

To build with test.

```shell
mkdir build
cd build
cmake .. -DGNS_BUILD_TEST=ON
make
```

To build test with memorycheck.

```shell
mkdir build
cd build
cmake .. -DGNS_BUILD_TEST_MEMORYCHECK=ON
make
```

To build with benchmarks.

```shell
mkdir build
cd build
cmake .. -DGNS_BUILD_BENCHMARKS=ON
make
```

To build examples.

```shell
mkdir build
cd build
cmake .. -DGNS_BUILD_EXAMPLES=ON
make
```

Build with all features

```
mkdir build
cd build
cmake .. -DGNS_BUILD_TEST=ON -DGNS_BUILD_TEST_MEMORYCHECK=ON -DGNS_BUILD_BENCHMARKS=ON -DGNS_BUILD_EXAMPLES=ON
make
```

## Contributions
This repository contains `Dockerfile` to run valgrind locally based on ubutu:14.04.
The `Dockerfile` is useful to debug error in Travis CI.
See README.md in docker/docker_valgrind.

### How to build documents
Just executes following command

```
bash scripts/docker_run_generate_docs.sh
```
