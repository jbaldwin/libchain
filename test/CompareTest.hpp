#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("cmp case sensitive")
{
    REQUIRE(chain::str::cmp("dErP", "dErP"));
    REQUIRE_FALSE(chain::str::cmp("herp", "HERP"));
}

TEST_CASE("cmp case insensitive")
{
    using Case = chain::str::Case;
    REQUIRE(chain::str::cmp("dErP", "dErP", Case::INSENSITIVE));
    REQUIRE(chain::str::cmp("dErP", "DeRp", Case::INSENSITIVE));
    REQUIRE(chain::str::cmp("herp", "HERP", Case::INSENSITIVE));
}

TEST_CASE("cmp different lengths")
{
    REQUIRE_FALSE(chain::str::cmp("abcd", "abc"));
}

TEST_CASE("starts with sensitive")
{
    REQUIRE(chain::str::starts_with("abcdefg", "a"));
    REQUIRE(chain::str::starts_with("abcdefg", "ab"));
    REQUIRE(chain::str::starts_with("abcdefg", "abc"));
    REQUIRE(chain::str::starts_with("abcdefg", "abcd"));
    REQUIRE(chain::str::starts_with("abcdefg", "abcde"));
    REQUIRE(chain::str::starts_with("abcdefg", "abcdef"));
    REQUIRE(chain::str::starts_with("abcdefg", "abcdefg"));
    REQUIRE_FALSE(chain::str::starts_with("abcdefg", "ABCDEFG"));
}

TEST_CASE("starts with insensitive")
{
    using Case = chain::str::Case;
    REQUIRE(chain::str::starts_with("abcdefg", "A", Case::INSENSITIVE));
    REQUIRE(chain::str::starts_with("abcdefg", "AB", Case::INSENSITIVE));
    REQUIRE(chain::str::starts_with("abcdefg", "ABC", Case::INSENSITIVE));
    REQUIRE(chain::str::starts_with("ABCDEFG", "abcd", Case::INSENSITIVE));
    REQUIRE(chain::str::starts_with("ABCDEFG", "abcde", Case::INSENSITIVE));
    REQUIRE(chain::str::starts_with("aBcDeFg", "AbCdEfG", Case::INSENSITIVE));
    REQUIRE(chain::str::starts_with("abcdefg", "ABCDEFG", Case::INSENSITIVE));
}

TEST_CASE("starts with longer start")
{
    REQUIRE_FALSE(chain::str::starts_with("a", "ab"));
}

TEST_CASE("end with sensitive")
{
    REQUIRE(chain::str::ends_with("abcdefg", "g"));
    REQUIRE(chain::str::ends_with("abcdefg", "fg"));
    REQUIRE(chain::str::ends_with("abcdefg", "efg"));
    REQUIRE(chain::str::ends_with("abcdefg", "defg"));
    REQUIRE(chain::str::ends_with("abcdefg", "cdefg"));
    REQUIRE(chain::str::ends_with("abcdefg", "bcdefg"));
    REQUIRE(chain::str::ends_with("abcdefg", "abcdefg"));
    REQUIRE_FALSE(chain::str::ends_with("ABCDEFG", "abcdefg"));
}

TEST_CASE("end with insensitive")
{
    using Case = chain::str::Case;
    REQUIRE(chain::str::ends_with("abcdefg", "G", Case::INSENSITIVE));
    REQUIRE(chain::str::ends_with("abcdefg", "FG", Case::INSENSITIVE));
    REQUIRE(chain::str::ends_with("abcdefg", "EFG", Case::INSENSITIVE));
    REQUIRE(chain::str::ends_with("ABCDEFG", "defg", Case::INSENSITIVE));
    REQUIRE(chain::str::ends_with("ABCDEFG", "cdefg", Case::INSENSITIVE));
    REQUIRE(chain::str::ends_with("aBcDeFg", "BcDeFg", Case::INSENSITIVE));
    REQUIRE(chain::str::ends_with("abcdefg", "ABCDEFG", Case::INSENSITIVE));
}

TEST_CASE("end with longer end")
{
    REQUIRE_FALSE(chain::str::ends_with("a", "Ab"));
}