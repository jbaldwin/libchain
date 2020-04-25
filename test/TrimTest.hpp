#pragma once

#include "catch.hpp"

#include <chain/Chain.hpp>

TEST_CASE("trim_left")
{
    {
        std::string data = "";
        chain::str::trim_left(data);
        REQUIRE(data.empty());
    }

    {
        std::string data = "                  ";
        chain::str::trim_left(data);
        REQUIRE(data.empty());
    }

    {
        std::string data = " a";
        chain::str::trim_left(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = " A";
        chain::str::trim_left(data);
        REQUIRE(data == "A");
    }

    {
        std::string data = "\na";
        chain::str::trim_left(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\ra";
        chain::str::trim_left(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\ta";
        chain::str::trim_left(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\va";
        chain::str::trim_left(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = " \n\r\t\va";
        chain::str::trim_left(data);
        REQUIRE(data == "a");
    }
}

TEST_CASE("trim_left with to remove")
{
    {
        std::string data = "";
        chain::str::trim_left(data, "abc");
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcdef";
        chain::str::trim_left(data, "abc");
        REQUIRE(data == "def");
    }

    {
        std::string data = "abcabcdef";
        chain::str::trim_left(data, "abc");
        REQUIRE(data == "def");
    }

    {
        std::string data = "abcdefabc";
        chain::str::trim_left(data, "abc");
        REQUIRE(data == "defabc");
    }
}

TEST_CASE("trim_left with to remove multiple")
{
    {
        std::string data = "";
        chain::str::trim_left(data, { "abc", "def" });
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcdef";
        chain::str::trim_left(data, { "abc", "def" });
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcabcdefefg";
        chain::str::trim_left(data, { "abc", "def" });
        REQUIRE(data == "efg");
    }

    {
        std::string data = "abcdefefg";
        chain::str::trim_left(data, { "abc", "def" });
        REQUIRE(data == "efg");
    }

    {
        std::string data = "abcdefefg";
        chain::str::trim_left(data, { "abc", "efg" });
        REQUIRE(data == "defefg");
    }
}

TEST_CASE("trim_left_view")
{
    REQUIRE(chain::str::trim_left_view("").empty());
    REQUIRE(chain::str::trim_left_view("                  ").empty());
    REQUIRE(chain::str::trim_left_view(" a") == "a");
    REQUIRE(chain::str::trim_left_view(" A") == "A");
    REQUIRE(chain::str::trim_left_view("\na") == "a");
    REQUIRE(chain::str::trim_left_view("\ra") == "a");
    REQUIRE(chain::str::trim_left_view("\ta") == "a");
    REQUIRE(chain::str::trim_left_view("\va") == "a");
    REQUIRE(chain::str::trim_left_view(" \n\r\t\va") == "a");
}

TEST_CASE("trim_left_view with to remove")
{
    REQUIRE(chain::str::trim_left_view("", "abc").empty());
    REQUIRE(chain::str::trim_left_view("abcdef", "abc") == "def");
    REQUIRE(chain::str::trim_left_view("abcabcdef", "abc") == "def");
    REQUIRE(chain::str::trim_left_view("abcdefabc", "abc") == "defabc");
}

TEST_CASE("trim_left_view with to remove multiple")
{
    REQUIRE(chain::str::trim_left_view("", { "abc", "def" }).empty());
    REQUIRE(chain::str::trim_left_view("abc", std::vector<std::string_view> {}) == "abc");
    REQUIRE(chain::str::trim_left_view("abcdef", { "abc", "def" }).empty());
    REQUIRE(chain::str::trim_left_view("abcabcdefabcdefefg", { "abc", "def" }) == "efg");
    REQUIRE(chain::str::trim_left_view("abcdefefg", { "abc", "def" }) == "efg");
    REQUIRE(chain::str::trim_left_view("abcdefefg", { "abc", "efg" }) == "defefg");
}

TEST_CASE("trim_right")
{
    {
        std::string data = "";
        chain::str::trim_right(data);
        REQUIRE(data.empty());
    }

    {
        std::string data = "                  ";
        chain::str::trim_right(data);
        REQUIRE(data.empty());
    }

    {
        std::string data = "a ";
        chain::str::trim_right(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "A ";
        chain::str::trim_right(data);
        REQUIRE(data == "A");
    }

    {
        std::string data = "a\n";
        chain::str::trim_right(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "a\r";
        chain::str::trim_right(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "a\t";
        chain::str::trim_right(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "a\v";
        chain::str::trim_right(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "a \n\r\t\v";
        chain::str::trim_right(data);
        REQUIRE(data == "a");
    }
}

TEST_CASE("trim_right with to remove")
{
    {
        std::string data = "";
        chain::str::trim_right(data, "abc");
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcdef";
        chain::str::trim_right(data, "def");
        REQUIRE(data == "abc");
    }

    {
        std::string data = "abcdefdef";
        chain::str::trim_right(data, "def");
        REQUIRE(data == "abc");
    }

    {
        std::string data = "abcdefabc";
        chain::str::trim_right(data, "abc");
        REQUIRE(data == "abcdef");
    }
}

TEST_CASE("trim_right with to remove multiple")
{
    {
        std::string data = "";
        chain::str::trim_right(data, { "abc", "def" });
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcdef";
        chain::str::trim_right(data, { "abc", "def" });
        REQUIRE(data.empty());
    }

    {
        std::string data = "efgabcabcdef";
        chain::str::trim_right(data, { "abc", "def" });
        REQUIRE(data == "efg");
    }

    {
        std::string data = "efgabcdef";
        chain::str::trim_right(data, { "abc", "def" });
        REQUIRE(data == "efg");
    }

    {
        std::string data = "efgdefabc";
        chain::str::trim_right(data, { "abc", "efg" });
        REQUIRE(data == "efgdef");
    }
}

TEST_CASE("trim_right_view")
{
    REQUIRE(chain::str::trim_right_view("").empty());
    REQUIRE(chain::str::trim_right_view("                  ").empty());
    REQUIRE(chain::str::trim_right_view("a ") == "a");
    REQUIRE(chain::str::trim_right_view("A ") == "A");
    REQUIRE(chain::str::trim_right_view("a\n") == "a");
    REQUIRE(chain::str::trim_right_view("a\r") == "a");
    REQUIRE(chain::str::trim_right_view("a\t") == "a");
    REQUIRE(chain::str::trim_right_view("a\v") == "a");
    REQUIRE(chain::str::trim_right_view("a \n\r\t\v") == "a");
}

TEST_CASE("trim_right_view with to remove")
{
    REQUIRE(chain::str::trim_right_view("", "abc").empty());
    REQUIRE(chain::str::trim_right_view("abcdef", "def") == "abc");
    REQUIRE(chain::str::trim_right_view("defabcabc", "abc") == "def");
    REQUIRE(chain::str::trim_right_view("abcdefabc", "abc") == "abcdef");
}

TEST_CASE("trim_right_view with to remove multiple")
{
    REQUIRE(chain::str::trim_right_view("", { "abc", "def" }).empty());
    REQUIRE(chain::str::trim_right_view("abc", std::vector<std::string_view> {}) == "abc");
    REQUIRE(chain::str::trim_right_view("abcdef", { "abc", "def" }).empty());
    REQUIRE(chain::str::trim_right_view("efgabcabcdefabcdef", { "abc", "def" }) == "efg");
    REQUIRE(chain::str::trim_right_view("efgabcdef", { "abc", "def" }) == "efg");
    REQUIRE(chain::str::trim_right_view("efgdefabc", { "abc", "efg" }) == "efgdef");
}

TEST_CASE("trim")
{
    {
        std::string data = "";
        chain::str::trim(data);
        REQUIRE(data.empty());
    }

    {
        std::string data = "                  ";
        chain::str::trim(data);
        REQUIRE(data.empty());
    }

    {
        std::string data = " a ";
        chain::str::trim(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = " A ";
        chain::str::trim(data);
        REQUIRE(data == "A");
    }

    {
        std::string data = "\na\n";
        chain::str::trim(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\ra\r";
        chain::str::trim(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\ta\t";
        chain::str::trim(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\va\v";
        chain::str::trim(data);
        REQUIRE(data == "a");
    }

    {
        std::string data = "\v\t\r\n a \n\r\t\v";
        chain::str::trim(data);
        REQUIRE(data == "a");
    }
}

TEST_CASE("trim with to remove")
{
    {
        std::string data = "";
        chain::str::trim(data, "abc");
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcdef";
        chain::str::trim(data, "def");
        REQUIRE(data == "abc");
    }

    {
        std::string data = "abcdefdef";
        chain::str::trim(data, "def");
        REQUIRE(data == "abc");
    }

    {
        std::string data = "abcdefabc";
        chain::str::trim(data, "abc");
        REQUIRE(data == "def");
    }

    {
        std::string data = "abcdefabc";
        chain::str::trim(data, "def");
        REQUIRE(data == "abcdefabc");
    }
}

TEST_CASE("trim with to remove multiple")
{
    {
        std::string data = "";
        chain::str::trim(data, { "abc", "def" });
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcdef";
        chain::str::trim(data, { "abc", "def" });
        REQUIRE(data.empty());
    }

    {
        std::string data = "abcabcdefefgabcabcdef";
        chain::str::trim(data, { "abc", "def" });
        REQUIRE(data == "efg");
    }

    {
        std::string data = "abcdefefgabcdef";
        chain::str::trim(data, { "abc", "def" });
        REQUIRE(data == "efg");
    }

    {
        std::string data = "efgdefabc";
        chain::str::trim(data, { "abc", "efg" });
        REQUIRE(data == "def");
    }

    {
        std::string data = "abcdefefg";
        chain::str::trim(data, { "abc", "efg" });
        REQUIRE(data == "def");
    }
}

TEST_CASE("trim_view")
{
    REQUIRE(chain::str::trim_view("").empty());
    REQUIRE(chain::str::trim_view("                  ").empty());
    REQUIRE(chain::str::trim_view(" a ") == "a");
    REQUIRE(chain::str::trim_view(" A ") == "A");
    REQUIRE(chain::str::trim_view("\na\n") == "a");
    REQUIRE(chain::str::trim_view("\ra\r") == "a");
    REQUIRE(chain::str::trim_view("\ta\t") == "a");
    REQUIRE(chain::str::trim_view("\ta\v") == "a");
    REQUIRE(chain::str::trim_view("\v\t\r\n a \n\r\t\v") == "a");
}

TEST_CASE("trim_view with to remove")
{
    REQUIRE(chain::str::trim_view("", "abc").empty());
    REQUIRE(chain::str::trim_view("defabcdef", "def") == "abc");
    REQUIRE(chain::str::trim_view("abcabcdefabcabc", "abc") == "def");
    REQUIRE(chain::str::trim_view("abcdefabc", "abc") == "def");
    REQUIRE(chain::str::trim_view("abcdefabc", "def") == "abcdefabc");
}

TEST_CASE("trim_view with to remove multiple")
{
    REQUIRE(chain::str::trim_view("", { "abc", "def" }).empty());
    REQUIRE(chain::str::trim_view("abc", std::vector<std::string_view> {}) == "abc");
    REQUIRE(chain::str::trim_view("abcdef", { "abc", "def" }).empty());
    REQUIRE(chain::str::trim_view("abcabcdefabcdefefgabcabcdefabcdef", { "abc", "def" }) == "efg");
    REQUIRE(chain::str::trim_view("abcdefefgabcdef", { "abc", "def" }) == "efg");
    REQUIRE(chain::str::trim_view("efgdefabc", { "abc", "efg" }) == "def");
}
