# my-chess-game

In this repository I will document my development of implementing a chess engine in C++23.

# Build
```sh
cmake -S . -B build
cmake --build build --parallel 4
ctest --test-dir build --output-on-failure
./build/engine
```

Requires CMake 3.25+ and a C++23 compiler (GCC 13+, Clang 17+).

# Status
Setting up environment of project like skeleton, test, CI.
Get into chess engines.


## AI policy
As the main focus of this project is to improve my C++ skills, I don't use AI for generate code. Nevertheless I use claude AI for conceptual porpuse and code review.


