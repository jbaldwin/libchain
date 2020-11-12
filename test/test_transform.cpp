#include "catch.hpp"

#include <chain/chain.hpp>

TEST_CASE("to_lower")
{
    std::string data = "DERP";
    chain::str::to_lower(data);
    REQUIRE(data == "derp");
}

TEST_CASE("to_lower_copy")
{
    REQUIRE(chain::str::to_lower_copy("DERP") == "derp");
}

TEST_CASE("to_upper")
{
    std::string data = "derp";
    chain::str::to_upper(data);
    REQUIRE(data == "DERP");
}

TEST_CASE("to_upper_copy")
{
    REQUIRE(chain::str::to_upper_copy("derp") == "DERP");
}
