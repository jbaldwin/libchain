#include "catch.hpp"

#include <chain/chain.hpp>

TEST_CASE("strerror(errsv) -> std::string")
{
    {
        auto        error    = chain::str::strerror(EAGAIN);
        std::string expected = "Resource temporarily unavailable";
        REQUIRE(error == expected);
        REQUIRE(error.length() == expected.length());
    }
}
