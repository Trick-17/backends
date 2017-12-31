# backends
Interchangeable backends:
- C++
- CUDA
- OpenCL
- OpenACC


## Project Health

| Service | System | Compiler | Status |
| ------- | ------ | -------- | -----: |
|  [Travis-CI](https://travis-ci.org/Trick-17/backends) | Ubuntu 14.04<br>OSX | GCC 6<br>Clang | [![Build Status](https://travis-ci.org/Trick-17/backends.svg?branch=master)](https://travis-ci.org/Trick-17/backends) |
|  [AppVeyor](https://ci.appveyor.com/project/Trick-17/backends) | Windows | MSVC12 <br/> MSVC14 <br/> MSVC14.1 | [![Build status](https://ci.appveyor.com/api/projects/status/k7d43bdnl80kwuq2?svg=true)](https://ci.appveyor.com/project/Trick-17/backends) |


## Including this library in your code

TODO...


## Library usage

Filling a vector with a single value:
```C++
auto myVec = backends::vector<double>(2000);
backends::fill(myVec, 12.0);
```

Typical reductions:
```C++
auto myVec = backends::vector<double>{1, 2, 3, 4};
double sum  = backends::sum(myVec);
double mean = backends::mean(myVec);
// The sum should be 12, the mean should be 2.5
```