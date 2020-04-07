#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("split csv")
{
    auto parts = chain::str::split("1,2,3", ',');

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == "1");
    REQUIRE(parts[1] == "2");
    REQUIRE(parts[2] == "3");
}

TEST_CASE("split string view delim")
{
    auto parts = chain::str::split("1:-2:-3", ":-");

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == "1");
    REQUIRE(parts[1] == "2");
    REQUIRE(parts[2] == "3");
}

TEST_CASE("split no delim present")
{
    auto parts = chain::str::split("herpderp", ',');

    REQUIRE(parts.size() == 1);
    REQUIRE(parts[0] == "herpderp");
}

TEST_CASE("split leading delim")
{
    auto parts = chain::str::split(",herpderp", ',');

    REQUIRE(parts.size() == 2);
    REQUIRE(parts[0].empty());
    REQUIRE(parts[1] == "herpderp");
}

TEST_CASE("split trailing delim")
{
    auto parts = chain::str::split("herpderp,", ',');

    REQUIRE(parts.size() == 2);
    REQUIRE(parts[0] == "herpderp");
    REQUIRE(parts[1].empty());
}

TEST_CASE("split leading string view delim")
{
    auto parts = chain::str::split("xyzherpderp", "xyz");

    REQUIRE(parts.size() == 2);
    REQUIRE(parts[0].empty());
    REQUIRE(parts[1] == "herpderp");
}

TEST_CASE("split trailing string view delim")
{
    auto parts = chain::str::split("herpderpxyz", "xyz");

    REQUIRE(parts.size() == 2);
    REQUIRE(parts[0] == "herpderp");
    REQUIRE(parts[1].empty());
}

TEST_CASE("split leading and trailing delim")
{
    auto parts = chain::str::split(",herpderp,", ",");

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0].empty());
    REQUIRE(parts[1] == "herpderp");
    REQUIRE(parts[2].empty());
}

TEST_CASE("split leading and trailing string view delim")
{
    auto parts = chain::str::split("xyzherpderpxyz", "xyz");

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0].empty());
    REQUIRE(parts[1] == "herpderp");
    REQUIRE(parts[2].empty());
}

TEST_CASE("split_map csv to int")
{
    auto parts = chain::str::split_map<int64_t>("1,2,3", ',', [](auto part) {
        return chain::str::to_number<int64_t>(part).value_or(0);
    });

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == 1);
    REQUIRE(parts[1] == 2);
    REQUIRE(parts[2] == 3);
}
