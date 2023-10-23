#include "catch.hpp"
#include "pmb/2d/rect.hpp"

#include <type_traits>


TEST_CASE("pmb::rect<T>")
{
    SECTION("check values/types for default constructed pmb::rect<int>")
    {
        pmb::rect<int> r;

        REQUIRE(r.x0 == 0);
        REQUIRE(r.y0 == 0);
        REQUIRE(r.x1 == 0);
        REQUIRE(r.y1 == 0);

        REQUIRE(std::is_same<decltype(r.x0), int>::value == true);
        REQUIRE(std::is_same<decltype(r.y0), int>::value == true);
        REQUIRE(std::is_same<decltype(r.x1), int>::value == true);
        REQUIRE(std::is_same<decltype(r.y1), int>::value == true);
    }

    SECTION("check constructed values for a pmb::rect<int>")
    {
        pmb::rect<int> r{1, 5, 7, 4};

        REQUIRE(r.x0 == 1);
        REQUIRE(r.y0 == 5);
        REQUIRE(r.x1 == 7);
        REQUIRE(r.y1 == 4);
    }

    SECTION("check values/types for default constructed pmb::rect<float>")
    {
        pmb::rect<float> r;

        REQUIRE(r.x0 == 0.0f);
        REQUIRE(r.y0 == 0.0f);
        REQUIRE(r.x1 == 0.0f);
        REQUIRE(r.y1 == 0.0f);

        REQUIRE(std::is_same<decltype(r.x0), float>::value == true);
        REQUIRE(std::is_same<decltype(r.y0), float>::value == true);
        REQUIRE(std::is_same<decltype(r.x1), float>::value == true);
        REQUIRE(std::is_same<decltype(r.y1), float>::value == true);
    }

    SECTION("check constructed values for a pmb::rect<float>")
    {
        pmb::rect<float> r{1.5f, 3.4f, 9.1f, 1.0f};

        REQUIRE(r.x0 == 1.5f);
        REQUIRE(r.y0 == 3.4f);
        REQUIRE(r.x1 == 9.1f);
        REQUIRE(r.y1 == 1.0f);
    }

    SECTION("verify comparison operators")
    {
        pmb::rect<int> r0{1, 2, 3, 4};
        pmb::rect<int> r1{1, 2, 3, 4};

        pmb::rect<int> r2{0, 2, 3, 4};
        pmb::rect<int> r3{1, 0, 3, 4};
        pmb::rect<int> r4{1, 2, 0, 4};
        pmb::rect<int> r5{1, 2, 3, 0};

        REQUIRE(r0 == r0); REQUIRE(not (r0 != r0));
        REQUIRE(r0 == r1); REQUIRE(not (r0 != r1));

        REQUIRE(r0 != r2); REQUIRE(not (r0 == r2));
        REQUIRE(r0 != r3); REQUIRE(not (r0 == r3));
        REQUIRE(r0 != r4); REQUIRE(not (r0 == r4));
        REQUIRE(r0 != r5); REQUIRE(not (r0 == r5));
    }
}
