#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("replace")
{
    std::string haystack = "derp";
    auto count = chain::str::replace(haystack, "d", "h");
    REQUIRE(haystack == "herp");
    REQUIRE(count == 1);
}

TEST_CASE("replace_copy simple")
{
    std::string original = "derp";
    auto [data, count] = chain::str::replace_copy(original, "d", "h");
    REQUIRE(data == "herp");
    REQUIRE(count == 1);
    REQUIRE(original == "derp");
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

TEST_CASE("replace insensitive")
{
    using Case = chain::str::Case;
    std::string haystack = "derp";
    auto count = chain::str::replace(haystack, "D", "H", Case::INSENSITIVE);
    REQUIRE(haystack == "Herp");
    REQUIRE(count == 1);
}

TEST_CASE("replace insensitive lots")
{
    using Case = chain::str::Case;
    std::string haystack = "ddddddddddddddddddddddddddddddddddddddddddd";
    auto count = chain::str::replace(haystack, "D", "H", Case::INSENSITIVE);
    REQUIRE(haystack == "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
    REQUIRE(count == 43);
}

TEST_CASE("replace insensitive lots max count")
{
    using Case = chain::str::Case;
    std::string haystack = "ddddddddddddddddddddddddddddddddddddddddddd";
    auto count = chain::str::replace(haystack, "D", "H", Case::INSENSITIVE, 25);
    REQUIRE(haystack == "HHHHHHHHHHHHHHHHHHHHHHHHHdddddddddddddddddd");
    REQUIRE(count == 25);
}

TEST_CASE("replace insenstive with bigger words")
{
    using Case = chain::str::Case;
    std::string haystack = "abc|ABC|Abc|aBc|abC|AbC|aBc";
    auto count = chain::str::replace(haystack, "AbC", "xYz", Case::INSENSITIVE);
    REQUIRE(haystack == "xYz|xYz|xYz|xYz|xYz|xYz|xYz");
    REQUIRE(count == 7);
}

TEST_CASE("replace insenstive with bigger words max coun")
{
    using Case = chain::str::Case;
    std::string haystack = "abc|ABC|Abc|aBc|abC|AbC|aBc";
    auto count = chain::str::replace(haystack, "AbC", "xYz", Case::INSENSITIVE, 3);
    REQUIRE(haystack == "xYz|xYz|xYz|aBc|abC|AbC|aBc");
    REQUIRE(count == 3);
}