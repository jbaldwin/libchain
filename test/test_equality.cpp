#include "catch.hpp"

#include <chain/chain.hpp>

TEST_CASE("equal case sensitive")
{
    REQUIRE(chain::str::equal("dErP", "dErP"));
    REQUIRE_FALSE(chain::str::equal("herp", "HERP"));
}

TEST_CASE("equal case insensitive")
{
    using case_t = chain::str::case_t;
    REQUIRE(chain::str::equal<case_t::insensitive>("dErP", "dErP"));
    REQUIRE(chain::str::equal<case_t::insensitive>("dErP", "DeRp"));
    REQUIRE(chain::str::equal<case_t::insensitive>("herp", "HERP"));
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
    using case_t = chain::str::case_t;
    REQUIRE(chain::str::starts_with<case_t::insensitive>("abcdefg", "A"));
    REQUIRE(chain::str::starts_with<case_t::insensitive>("abcdefg", "AB"));
    REQUIRE(chain::str::starts_with<case_t::insensitive>("abcdefg", "ABC"));
    REQUIRE(chain::str::starts_with<case_t::insensitive>("ABCDEFG", "abcd"));
    REQUIRE(chain::str::starts_with<case_t::insensitive>("ABCDEFG", "abcde"));
    REQUIRE(chain::str::starts_with<case_t::insensitive>("aBcDeFg", "AbCdEfG"));
    REQUIRE(chain::str::starts_with<case_t::insensitive>("abcdefg", "ABCDEFG"));
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
    using case_t = chain::str::case_t;
    REQUIRE(chain::str::ends_with<case_t::insensitive>("abcdefg", "G"));
    REQUIRE(chain::str::ends_with<case_t::insensitive>("abcdefg", "FG"));
    REQUIRE(chain::str::ends_with<case_t::insensitive>("abcdefg", "EFG"));
    REQUIRE(chain::str::ends_with<case_t::insensitive>("ABCDEFG", "defg"));
    REQUIRE(chain::str::ends_with<case_t::insensitive>("ABCDEFG", "cdefg"));
    REQUIRE(chain::str::ends_with<case_t::insensitive>("aBcDeFg", "BcDeFg"));
    REQUIRE(chain::str::ends_with<case_t::insensitive>("abcdefg", "ABCDEFG"));
}

TEST_CASE("ends_with longer end")
{
    REQUIRE_FALSE(chain::str::ends_with("a", "Ab"));
}
