[![Build Status](https://travis-ci.org/i05nagai/generalized_niederreiter_sequence.svg?branch=master)](https://travis-ci.org/i05nagai/generalized_niederreiter_sequence)

## Overviews

## Build

```shell
cmake .
make
```

To build test.

```shell
cmake . -DGF_BUILD_TEST=ON
make
```

To build test with memorycheck.

```shell
cmake . -DGF_BUILD_TEST_MEMORYCHECK=ON
make
```

To build benchmarks.

```shell
cmake . -DGF_BUILD_BENCHMARKS=ON
make
```

To build examples.

```shell
cmake . -DGF_BUILD_EXAMPLES=ON
make
```
