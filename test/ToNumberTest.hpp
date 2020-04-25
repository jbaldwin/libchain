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

TEST_CASE("integer invalid")
{
    auto value = chain::str::to_number<int>("a1234567890");

    REQUIRE_FALSE(value.has_value());
}

TEST_CASE("float")
{
    std::string data { "1.234" };
    auto value = chain::str::to_number<float>(data);

    REQUIRE(value.has_value());
    REQUIRE(std::to_string(value.value()) == "1.234000");
}

TEST_CASE("double")
{
    std::string data { "1.23456789" };
    auto value = chain::str::to_number<double>(data);

    REQUIRE(value.has_value());
    REQUIRE(std::to_string(value.value()) == "1.234568");
}

TEST_CASE("long double")
{
    std::string data { "1.234567890123456789" };
    auto value = chain::str::to_number<long double>(data);

    REQUIRE(value.has_value());
    REQUIRE(std::to_string(value.value()) == "1.234568");
}

TEST_CASE("float invalid")
{
    std::string data { "a1.234" };
    auto value = chain::str::to_number<float>(data);

    REQUIRE_FALSE(value.has_value());
}

TEST_CASE("is_int")
{
    REQUIRE(chain::str::is_int("1234567890"));
    REQUIRE_FALSE(chain::str::is_int("1.4"));
}

TEST_CASE("is_float")
{
    REQUIRE(chain::str::is_float("12345.67890"));
    REQUIRE_FALSE(chain::str::is_float("14"));
}

TEST_CASE("is_number")
{
    REQUIRE(chain::str::is_number("1234567890"));
    REQUIRE(chain::str::is_number("1.4"));
}