#include "catch.hpp"
#include "cmm/buffer.hpp"


TEST_CASE("cmm::buffer")
{
    cmm::buffer b{100};

    REQUIRE(b.data() != nullptr);
    REQUIRE(b.size() == 100);
    REQUIRE(std::distance(b.begin(), b.end()) == 100);
    REQUIRE(std::distance(b.cbegin(), b.cend()) == 100);
}
