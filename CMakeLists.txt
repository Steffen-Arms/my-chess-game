cmake_minimum_required(VERSION 3.25)

project(chess_engine VERSION 0.1.0 LANGUAGES CXX)

# --- Language standard -------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)            # std::expected needs C++23
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # this enforce the use of C++23. If the compiler is not compatible it fail.
set(CMAKE_CXX_EXTENSIONS OFF)         # turn on -std=c++23, turn off default version-std=gnu++23 from "set(CMAKE_CXX_STANDARD 23)". WHY: std=gnu++23 have some special GNU features and don't run on every compiler

# Writes build/compile_commands.json, which clangd / VS Code read
#this compile_commands.json lists the compiler commands for every .cpp file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Single-config generators (Make, Ninja) have no build type by default
#if no build type flag (debug or release) is set, it will define it to "Debug".
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()


# declare a option "ENGINE_SANITIZE" (ASAN (for memory) and UBSAN (for undefine behaviour))
# Note this option is OFF. We will turn it ON at the cmake command level
option(ENGINE_SANITIZE "Build with AddressSanitizer and UBSan" OFF)

# --- Shared compiler flags ---------------------------------------------------
# An INTERFACE library compiles nothing; it only carries settings to
# whatever links against it.
add_library(engine_flags INTERFACE)

if(MSVC)
  target_compile_options(engine_flags INTERFACE /W4 /permissive-)
else()
  target_compile_options(engine_flags INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion) # I will handle "warning as errors" in the CI.
  if(ENGINE_SANITIZE)
    target_compile_options(engine_flags INTERFACE
      -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(engine_flags INTERFACE -fsanitize=address,undefined)
  endif()
endif()

##########################################################################################
# We seperate main.cpp to all other .cpp files because we want to apply a test program 
# --- Engine library: all chess logic lives here ------------------------------
add_library(engine_core
  src/engine_info.cpp
  src/board.cpp
)
target_include_directories(engine_core PUBLIC src) #this line look for headers in src/
target_link_libraries(engine_core PUBLIC engine_flags) 

# --- Executable: only main(), later the UCI loop -----------------------------
add_executable(engine src/main.cpp)
target_link_libraries(engine PRIVATE engine_core) #this connect our main.cpp to the rest of the programm

# --- Tests -------------------------------------------------------------------
#we include the module CTest from CMake. BUILD_TESTING is define inside that model.
include(CTest)   # defines BUILD_TESTING (ON by default) and enables ctest
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
