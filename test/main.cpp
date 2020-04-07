#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("catch_is_working")
{
    CHECK(true);
}

#include "SplitTest.hpp"
#include "JoinTest.hpp"