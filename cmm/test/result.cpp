#include "catch.hpp"
#include "cmm/result.hpp"


TEST_CASE("cmm::result<T, E>")
{
    SECTION("construct with a value")
    {
        cmm::result<char, char> r{cmm::ok('A')};

        REQUIRE(r.value() == 'A');
        REQUIRE(r.is_valid() == true);
        REQUIRE_THROWS(r.error());
    }

    SECTION("construct with an error")
    {
        cmm::result<char, char> r{cmm::err('E')};

        REQUIRE(r.error() == 'E');
        REQUIRE(r.is_valid() == false);
        REQUIRE_THROWS(r.value());
    }
}
