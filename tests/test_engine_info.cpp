#include <catch2/catch_test_macros.hpp>

#include "engine_info.hpp"

TEST_CASE("engine reports a name and an author", "[info]")
{
    REQUIRE_FALSE(chess::engine_name().empty());
    REQUIRE_FALSE(chess::engine_author().empty());
}
