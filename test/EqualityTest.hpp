#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("equal case sensitive")
{
    REQUIRE(chain::str::equal("dErP", "dErP"));
    REQUIRE_FALSE(chain::str::equal("herp", "HERP"));
}

TEST_CASE("equal case insensitive")
{
    using Case = chain::str::Case;
    REQUIRE(chain::str::equal<Case::INSENSITIVE>("dErP", "dErP"));
    REQUIRE(chain::str::equal<Case::INSENSITIVE>("dErP", "DeRp"));
    REQUIRE(chain::str::equal<Case::INSENSITIVE>("herp", "HERP"));
}

TEST_CASE("equal different lengths")
{
    REQUIRE_FALSE(chain::str::equal("abcd", "abc"));
}

TEST_CASE("starts_with sensitive")
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

TEST_CASE("starts_with insensitive")
{
    using Case = chain::str::Case;
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("abcdefg", "A"));
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("abcdefg", "AB"));
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("abcdefg", "ABC"));
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("ABCDEFG", "abcd"));
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("ABCDEFG", "abcde"));
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("aBcDeFg", "AbCdEfG"));
    REQUIRE(chain::str::starts_with<Case::INSENSITIVE>("abcdefg", "ABCDEFG"));
}

TEST_CASE("starts_with longer start")
{
    REQUIRE_FALSE(chain::str::starts_with("a", "ab"));
}

TEST_CASE("ends_with sensitive")
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

TEST_CASE("ends_with insensitive")
{
    using Case = chain::str::Case;
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("abcdefg", "G"));
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("abcdefg", "FG"));
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("abcdefg", "EFG"));
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("ABCDEFG", "defg"));
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("ABCDEFG", "cdefg"));
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("aBcDeFg", "BcDeFg"));
    REQUIRE(chain::str::ends_with<Case::INSENSITIVE>("abcdefg", "ABCDEFG"));
}

TEST_CASE("ends_with longer end")
{
    REQUIRE_FALSE(chain::str::ends_with("a", "Ab"));
}