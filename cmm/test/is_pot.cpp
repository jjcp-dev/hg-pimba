#include "catch.hpp"
#include "cmm/is_pot.hpp"


TEST_CASE("cmm::is_pot<T>()")
{
    SECTION("T == int")
    {
        REQUIRE(cmm::is_pot<int>(0) == false);
        REQUIRE(cmm::is_pot<int>(1) == true);
        REQUIRE(cmm::is_pot<int>(2) == true);
        REQUIRE(cmm::is_pot<int>(3) == false);
        REQUIRE(cmm::is_pot<int>(4) == true);
        REQUIRE(cmm::is_pot<int>(5) == false);
        REQUIRE(cmm::is_pot<int>(6) == false);
        REQUIRE(cmm::is_pot<int>(7) == false);
        REQUIRE(cmm::is_pot<int>(8) == true);
        REQUIRE(cmm::is_pot<int>(9) == false);
        REQUIRE(cmm::is_pot<int>(10) == false);

        REQUIRE(cmm::is_pot<int>(16) == true);
        REQUIRE(cmm::is_pot<int>(32) == true);
        REQUIRE(cmm::is_pot<int>(64) == true);
        REQUIRE(cmm::is_pot<int>(128) == true);
        REQUIRE(cmm::is_pot<int>(256) == true);
        REQUIRE(cmm::is_pot<int>(512) == true);
        REQUIRE(cmm::is_pot<int>(1024) == true);
    }

    SECTION("T == int (negatives)")
    {
        REQUIRE(cmm::is_pot<int>(-1) == false);
        REQUIRE(cmm::is_pot<int>(-2) == false);
        REQUIRE(cmm::is_pot<int>(-3) == false);
        REQUIRE(cmm::is_pot<int>(-4) == false);
        REQUIRE(cmm::is_pot<int>(-5) == false);
        REQUIRE(cmm::is_pot<int>(-6) == false);
        REQUIRE(cmm::is_pot<int>(-7) == false);
        REQUIRE(cmm::is_pot<int>(-8) == false);
        REQUIRE(cmm::is_pot<int>(-9) == false);
        REQUIRE(cmm::is_pot<int>(-10) == false);

        REQUIRE(cmm::is_pot<int>(-16) == false);
        REQUIRE(cmm::is_pot<int>(-32) == false);
        REQUIRE(cmm::is_pot<int>(-64) == false);
        REQUIRE(cmm::is_pot<int>(-128) == false);
        REQUIRE(cmm::is_pot<int>(-256) == false);
        REQUIRE(cmm::is_pot<int>(-512) == false);
        REQUIRE(cmm::is_pot<int>(-1024) == false);
    }
}
