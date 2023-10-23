#include "catch.hpp"
#include "cmm/byte.hpp"
#include <limits>


TEST_CASE("cmm::byte")
{
    REQUIRE(std::numeric_limits<cmm::byte>::max() == 255);
    REQUIRE(std::numeric_limits<cmm::byte>::min() == 0);
}
