#include "catch.hpp"

#include <chain/chain.hpp>

TEST_CASE("split csv")
{
    auto parts = chain::str::split("1,2,3", ',');

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == "1");
    REQUIRE(parts[1] == "2");
    REQUIRE(parts[2] == "3");
}

TEST_CASE("split csv with out param")
{
    std::vector<std::string_view> parts;
    parts.reserve(3);
    chain::str::split("1,2,3", ',', parts);

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
    auto parts = chain::str::split_map<int64_t>(
        "1,2,3", ',', [](auto part) { return chain::str::to_number<int64_t>(part).value_or(0); });

    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == 1);
    REQUIRE(parts[1] == 2);
    REQUIRE(parts[2] == 3);
}

TEST_CASE("split_for_each char empty string")
{
    uint64_t called{0};
    chain::str::split_for_each("", '\n', [&](std::string_view) {
        ++called;
        return true;
    });

    REQUIRE(called == 1);
}

TEST_CASE("split_for_each string_view empty string")
{
    uint64_t called{0};
    chain::str::split_for_each("", "\n", [&](std::string_view) {
        ++called;
        return true;
    });

    REQUIRE(called == 1);
}

TEST_CASE("split_for_each csv")
{
    uint64_t called{0};
    chain::str::split_for_each("1,2,3333,4", ",", [&](std::string_view s) -> bool {
        ++called;

        switch(called)
        {
            case 1:
                REQUIRE(s == "1");
                break;
            case 2:
                REQUIRE(s == "2");
                break;
            case 3:
                REQUIRE(s == "3333");
                break;
            case 4:
                REQUIRE(s == "4");
                break;
        }

        return true;
    });

    REQUIRE(called == 4);
}

TEST_CASE("split_for_each stop early")
{
    uint64_t called{0};
    chain::str::split_for_each("1,2,3,4,5,6,7,8,9,10", ",", [&](std::string_view s) -> bool {
        ++called;

        if(called >= 3)
        {
            return false;
        }

        return true;
    });

    REQUIRE(called == 3);
}
