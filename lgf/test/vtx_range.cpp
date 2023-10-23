#include "catch.hpp"
#include "lgf/vtx_range.hpp"


TEST_CASE("lgf::vtx_range")
{
    SECTION("construction")
    {
        lgf::vtx_range r0;

        REQUIRE(r0.start() == 0);
        REQUIRE(r0.count() == 0);

        lgf::vtx_range r1{21, 31};

        REQUIRE(r1.start() == 21);
        REQUIRE(r1.count() == 31);
    }

    SECTION("comparison operators")
    {
        lgf::vtx_range r0{1, 2};
        lgf::vtx_range r1{1, 3};
        lgf::vtx_range r2{3, 2};
        lgf::vtx_range r3{5, 6};
        lgf::vtx_range r4{5, 6};

        REQUIRE(r0 != r1);
        REQUIRE(r0 != r2);
        REQUIRE(r0 != r3);
        REQUIRE(not (r3 != r4));

        REQUIRE(not (r0 == r1));
        REQUIRE(not (r0 == r2));
        REQUIRE(not (r0 == r3));
        REQUIRE(r3 == r4);
    }
}
