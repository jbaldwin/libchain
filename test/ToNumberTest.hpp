#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("integer")
{
    auto value = chain::str::to_number<int>("1");

    REQUIRE(value.has_value());
    REQUIRE(value.value() == 1);
}

TEST_CASE("integer leading +")
{
    auto value = chain::str::to_number<int>("+1");

    REQUIRE(value.has_value());
    REQUIRE(value.value() == 1);
}

TEST_CASE("integer leading -")
{
    auto value = chain::str::to_number<int>("-1");

    REQUIRE(value.has_value());
    REQUIRE(value.value() == -1);
}

TEST_CASE("unsigned integer")
{
    auto value = chain::str::to_number<unsigned int>("1");

    REQUIRE(value.has_value());
    REQUIRE(value.value() == 1);
}

TEST_CASE("unsigned integer leading +")
{
    auto value = chain::str::to_number<unsigned int>("+1");

    REQUIRE(value.has_value());
    REQUIRE(value.value() == 1);
}

TEST_CASE("unsigned integer leading -")
{
    auto value = chain::str::to_number<unsigned int>("-1");

    REQUIRE(!value.has_value());
}

TEST_CASE("integer 0-9")
{
    auto value = chain::str::to_number<int>("1234567890");

    REQUIRE(value.has_value());
    REQUIRE(value.value() == 1234567890);
}

TEST_CASE("float")
{
    std::string data{"1.234"};
    auto value = chain::str::to_number<float>(data);

    REQUIRE(value.has_value());
    REQUIRE(std::to_string(value.value()) == "1.234000");
}

TEST_CASE("double")
{
    std::string data{"1.23456789"};
    auto value = chain::str::to_number<double>(data);

    REQUIRE(value.has_value());
    REQUIRE(std::to_string(value.value()) == "1.234568");
}

TEST_CASE("long double")
{
    std::string data{"1.234567890123456789"};
    auto value = chain::str::to_number<long double>(data);

    REQUIRE(value.has_value());
    REQUIRE(std::to_string(value.value()) == "1.234568");
}
