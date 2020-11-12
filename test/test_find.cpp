#include "catch.hpp"

#include <chain/chain.hpp>

TEST_CASE("find sensitive")
{
    using namespace chain::str;
    REQUIRE(find("asdfjsldkfjslkdjfderpldkjfl", "derp") == 17);
    REQUIRE(find("asdfjsldkfjslkdjfpderldkjfl", "derp") == std::string_view::npos);
    REQUIRE(find("asdfjsldkfjslkdjfDERPldkjfl", "derp") == std::string_view::npos);
    REQUIRE(find("asdfjsldkfjslkdjfDERPldkjfl", "DERP") == 17);
    REQUIRE(find("aaaaaaaaaaaaaaaaaaaaaderp", "derp") == 21);
    REQUIRE(find("derpaaaaaaaaaaaaaaaaaaaaa", "derp") == 0);
    REQUIRE(find("derpaaaaaaaaaaaaaaaaaderp", "derp") == 0);

    REQUIRE(find("abcdefghijklmnopabc", "abc") == 0);
    REQUIRE(find("abcdefghijklmnop", "abc", 1) == std::string_view::npos);
    REQUIRE(find("abcdefghijklmnopdcb", "bcd", 1) == 1);
    REQUIRE(find("abcdefghijklmnop", "mno", 5) == 12);
}

TEST_CASE("find insensitive")
{
    using namespace chain::str;
    REQUIRE(find<case_t::insensitive>("asdfjsldkfjslkdjfDERPldkjfl", "derp") == 17);
    REQUIRE(find<case_t::insensitive>("asdfjsldkfjslkdjfpDeRldkjfl", "derp") == std::string_view::npos);
    REQUIRE(find<case_t::insensitive>("asdfjsldkfjslkdjfDERPldkjfl", "derp") == 17);
    REQUIRE(find<case_t::insensitive>("asdfjsldkfjslkdjfDERPldkjfl", "DERP", 4) == 17);
    REQUIRE(find<case_t::insensitive>("aaaaaaaaaaaaaaaaaaaaaDERp", "derp") == 21);
    REQUIRE(find<case_t::insensitive>("dERPaaaaaaaaaaaaaaaaaaaaa", "derp") == 0);
    REQUIRE(find<case_t::insensitive>("derpaaaaaaaaaaaaaaaaaderp", "DERP") == 0);
}

TEST_CASE("rfind sensitive")
{
    using namespace chain::str;
    REQUIRE(rfind("asdfjsldkfjslkdjfderpldkjfl", "derp") == 17);
    REQUIRE(rfind("asdfjsldkfjslkdjfpderldkjfl", "derp") == std::string_view::npos);
    REQUIRE(rfind("asdfjsldkfjslkdjfDERPldkjfl", "derp") == std::string_view::npos);
    REQUIRE(rfind("asdfjsldkfjslkdjfDERPldkjfl", "DERP") == 17);
    REQUIRE(rfind("aaaaaaaaaaaaaaaaaaaaaderp", "derp") == 21);
    REQUIRE(rfind("derpaaaaaaaaaaaaaaaaaaaaa", "derp") == 0);
    REQUIRE(rfind("derpaaaaaaaaaaaaaaaaaderp", "DERP") == std::string_view::npos);
    REQUIRE(rfind("derpaaaaaaaaaaaaaaaaaderp", "derp") == 21);

    REQUIRE(rfind("abcdefghijklmnopabc", "abc") == 16);
    REQUIRE(rfind("abcdefghijklmnopabc", "abc", 18) == 16);
    REQUIRE(rfind("abcdefghijklmnopdcb", "bcd", 18) == 1);
    REQUIRE(rfind("abcdefghijklmnop", "mno", 10) == std::string_view::npos);
}

TEST_CASE("rfind insensitive")
{
    using namespace chain::str;
    REQUIRE(rfind<case_t::insensitive>("asdfjsldkfjslkdjfDERPldkjfl", "derp") == 17);
    REQUIRE(rfind<case_t::insensitive>("asdfjsldkfjslkdjfpDeRldkjfl", "derp") == std::string_view::npos);
    REQUIRE(rfind<case_t::insensitive>("asdfjsldkfjslkdjfDERPldkjfl", "derp") == 17);
    REQUIRE(rfind<case_t::insensitive>("asdfjsldkfjslkdjfDERPldkjfl", "DERP") == 17);
    REQUIRE(rfind<case_t::insensitive>("aaaaaaaaaaaaaaaaaaaaaDERp", "derp") == 21);
    REQUIRE(rfind<case_t::insensitive>("dERPaaaaaaaaaaaaaaaaaaaaa", "derp") == 0);
    REQUIRE(rfind<case_t::insensitive>("derpaaaaaaaaaaaaaaaaaderp", "DERP") == 21);
    REQUIRE(rfind<case_t::insensitive>("derpaaaaaaaaaaaaaaaaaderp", "DERP", 22) == 0);
    REQUIRE(rfind<case_t::insensitive>("derpaaaaaaaaaaaaaaaaaderp", "DERP", 20) == 0);
}
