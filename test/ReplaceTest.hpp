#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("replace simple")
{
    std::string haystack = "derp";
    auto count = chain::str::replace(haystack, "d", "h");
    REQUIRE(haystack == "herp");
    REQUIRE(count == 1);
}

TEST_CASE("replace_copy simple")
{
    auto [data, count] = chain::str::replace_copy("derp", "d", "h");
    REQUIRE(data == "herp");
    REQUIRE(count == 1);
}

TEST_CASE("replace with count")
{
    using Case = chain::str::Case;
    {
        auto [data, count] = chain::str::replace_copy("abc abc abc", "abc", "cba", Case::SENSITIVE, 2);
        REQUIRE(count == 2);
        REQUIRE(data == "cba cba abc");
    }

    {
        // more than in the string
        auto [data, count] = chain::str::replace_copy("abc abc abc", "abc", "cba", Case::SENSITIVE, 10);
        REQUIRE(count == 3);
        REQUIRE(data == "cba cba cba");
    }

    {
        auto [data, count] = chain::str::replace_copy("abc abc abc", "abc", "cba", Case::SENSITIVE, 0);
        REQUIRE(count == 0);
        REQUIRE(data == "abc abc abc");
    }
}