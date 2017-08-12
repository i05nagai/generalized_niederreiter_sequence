[![Build Status](https://travis-ci.org/i05nagai/generalized_niederreiter_sequence.svg?branch=master)](https://travis-ci.org/i05nagai/generalized_niederreiter_sequence)

## Overviews

## Build

```shell
mkdir build
cd build
cmake ..
make
```

To build test.

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

To build benchmarks.

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
