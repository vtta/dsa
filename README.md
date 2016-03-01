[![Build Status](https://travis-ci.org/bsamseth/cpp-project.svg?branch=master)](https://travis-ci.org/bsamseth/cpp-project)
[![Coverage Status](https://coveralls.io/repos/github/bsamseth/cpp-project/badge.svg?branch=master)](https://coveralls.io/github/bsamseth/cpp-project?branch=master)

# Boiler plate for C++ projects 

This is a boiler plate for C++ projects. What you get:

- Sources, headers and mains separated in distinct folders
- Access to Google Tests
- Use of CMake for much easier compiling
- Continuous testing with Travis-CI
- Code coverage with Coveralls.io

### Structure
Sources go in [src/](src/), header files in [include/](include/), main programs in [app/] (must be added to [CMakeLists.txt]),
tests go in [tests/] (compiled in unit_tests.x by default).

Ignored files are Emacs backup files, executables and the build/ dir.

### Building

Build by making a build directory (i.e. build/), run CMake in that dir, and then use Make to build the desired target.

Example:

``` bash
$ mkdir build && cd build
$ cmake .. # argument is location of CMakelists.txt
$ make
$ ./unit_tests.x
```



### Services

If repository is activated with Travis-CI, then unit tests will be built and executed on each commit.

If repository is activated with Coveralls, then deployment to Travis will also calculate code coverage and
upload this to Coveralls.io. 


