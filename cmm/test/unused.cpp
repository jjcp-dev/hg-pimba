#include "catch.hpp"
#include "cmm/unused.hpp"


TEST_CASE("cmm::unused(T...)")
{
    SECTION("check function does not modify any parameters")
    {
        int a = 2;
        cmm::unused(a);

        REQUIRE(a == 2);

        int b = 3;
        int c = 1;
        float d = 4.78f;
        cmm::unused(b, c, d);

        REQUIRE(b == 3);
        REQUIRE(c == 1);
        REQUIRE(d == 4.78f);

        const int e = 8;
        cmm::unused(e, 1, "", c);

        REQUIRE(e == 8);
        REQUIRE(c == 1);
    }
}
