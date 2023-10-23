#include "catch.hpp"
#include "cmm/bit_ops.hpp"


enum class T {
    none = 0,
    a = 1 << 0,
    b = 1 << 1,
    c = 1 << 2,
    d = 1 << 3,
};

CMM_DEFINE_BIT_OPERATORS(T)


TEST_CASE("cmm/bit_ops")
{
    REQUIRE((T::c & T::c) == T::c);
    REQUIRE((T::a & T::b) == T::none);
    REQUIRE((~T::a & T::a) == T::none);
    REQUIRE((~T::a & T::b) == T::b);
    REQUIRE((~T::a & T::c) == T::c);
    REQUIRE((~T::a & T::d) == T::d);

    {
        auto v = (T::a | T::b | T::c) ^ T::b;
        REQUIRE((v & T::b) == T::none);
        REQUIRE(((v ^ T::b) & T::b) == T::b);
    }

    REQUIRE(cmm::any(T::none) == false);
    REQUIRE(cmm::any(T::a & T::b) == false);
    REQUIRE(cmm::any(T::a) == true);
    REQUIRE(cmm::any(T::b) == true);
    REQUIRE(cmm::any(T::c) == true);
    REQUIRE(cmm::any(T::d) == true);
    REQUIRE(cmm::any(T::a | T::b) == true);
}
