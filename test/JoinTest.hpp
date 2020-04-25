#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

#include <vector>

TEST_CASE("join csv")
{
    std::vector<int64_t> parts { 1, 2, 3 };
    auto joined = chain::str::join(parts, ',');
    REQUIRE(joined == "1,2,3");
}

TEST_CASE("join string view delim")
{
    std::vector<int64_t> parts { 1, 2, 3 };
    auto joined = chain::str::join(parts, ":-");
    REQUIRE(joined == "1:-2:-3");
}

TEST_CASE("join no parts")
{
    std::vector<int64_t> parts {};
    auto joined = chain::str::join(parts, ',');
    REQUIRE(joined.empty());
}

TEST_CASE("map_join csv")
{
    std::vector<int64_t> parts { 1, 2, 3 };
    auto joined = chain::str::map_join(parts, ',', [](int64_t x) { return x * x; });
    REQUIRE(joined == "1,4,9");
}

TEST_CASE("map_join string view delim")
{
    std::vector<int64_t> parts { 1, 2, 3 };
    auto joined = chain::str::map_join(parts, ":-", [](int64_t x) { return x * x; });
    REQUIRE(joined == "1:-4:-9");
}

TEST_CASE("map_join no parts")
{
    std::vector<int64_t> parts {};
    auto joined = chain::str::map_join(parts, ',', [](int64_t x) { return x * x; });
    REQUIRE(joined.empty());
}
