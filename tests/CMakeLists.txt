include(FetchContent)

# Downloads Catch2 at configure time and builds it with our project.
# Pinned to a tag so every machine (and CI) uses the same version.
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.16.0
  GIT_SHALLOW    TRUE
  SYSTEM         # treat its headers as system headers: no warnings from them
)
FetchContent_MakeAvailable(Catch2)

add_executable(engine_tests
  test_engine_info.cpp
)
# Catch2WithMain supplies main(), so test files only contain TEST_CASEs
target_link_libraries(engine_tests PRIVATE engine_core Catch2::Catch2WithMain)

# Registers every TEST_CASE as its own ctest entry
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(engine_tests)
