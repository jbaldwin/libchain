#include "catch.hpp"

#include <chain/chain.hpp>

TEST_CASE("replace")
{
    std::string haystack = "derp";
    auto        count    = chain::str::replace(haystack, "d", "h");
    REQUIRE(haystack == "herp");
    REQUIRE(count == 1);
}

TEST_CASE("replace_copy simple")
{
    std::string original = "derp";
    auto [data, count]   = chain::str::replace_copy(original, "d", "h");
    REQUIRE(data == "herp");
    REQUIRE(count == 1);
    REQUIRE(original == "derp");
}

TEST_CASE("replace with count")
{
    using case_t = chain::str::case_t;
    {
        auto [data, count] = chain::str::replace_copy("abc abc abc", "abc", "cba", 2);
        REQUIRE(count == 2);
        REQUIRE(data == "cba cba abc");
    }

    {
        // more than in the string
        auto [data, count] = chain::str::replace_copy("abc abc abc", "abc", "cba", 10);
        REQUIRE(count == 3);
        REQUIRE(data == "cba cba cba");
    }

    {
        auto [data, count] = chain::str::replace_copy("abc abc abc", "abc", "cba", 0);
        REQUIRE(count == 0);
        REQUIRE(data == "abc abc abc");
    }
}

TEST_CASE("replace insensitive")
{
    using case_t         = chain::str::case_t;
    std::string haystack = "derp";
    auto        count    = chain::str::replace<case_t::insensitive>(haystack, "D", "H");
    REQUIRE(haystack == "Herp");
    REQUIRE(count == 1);
}

TEST_CASE("replace insensitive lots")
{
    using case_t         = chain::str::case_t;
    std::string haystack = "ddddddddddddddddddddddddddddddddddddddddddd";
    auto        count    = chain::str::replace<case_t::insensitive>(haystack, "D", "H");
    REQUIRE(haystack == "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
    REQUIRE(count == 43);
}

TEST_CASE("replace insensitive lots max count")
{
    using case_t         = chain::str::case_t;
    std::string haystack = "ddddddddddddddddddddddddddddddddddddddddddd";
    auto        count    = chain::str::replace<case_t::insensitive>(haystack, "D", "H", 25);
    REQUIRE(haystack == "HHHHHHHHHHHHHHHHHHHHHHHHHdddddddddddddddddd");
    REQUIRE(count == 25);
}

TEST_CASE("replace insenstive with bigger words")
{
    using case_t         = chain::str::case_t;
    std::string haystack = "abc|ABC|Abc|aBc|abC|AbC|aBc";
    auto        count    = chain::str::replace<case_t::insensitive>(haystack, "AbC", "xYz");
    REQUIRE(haystack == "xYz|xYz|xYz|xYz|xYz|xYz|xYz");
    REQUIRE(count == 7);
}

TEST_CASE("replace insenstive with bigger words max coun")
{
    using case_t         = chain::str::case_t;
    std::string haystack = "abc|ABC|Abc|aBc|abC|AbC|aBc";
    auto        count    = chain::str::replace<case_t::insensitive>(haystack, "AbC", "xYz", 3);
    REQUIRE(haystack == "xYz|xYz|xYz|aBc|abC|AbC|aBc");
    REQUIRE(count == 3);
}
