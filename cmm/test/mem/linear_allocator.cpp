#include "catch.hpp"
#include "cmm/mem/linear_allocator.hpp"
#include "cmm/mem/align.hpp"


TEST_CASE("cmm::linear_allocator")
{
    SECTION("allocate the whole buffer")
    {
        char buffer[256];

        cmm::linear_allocator la{buffer};

        REQUIRE(la.capacity() == 256);

        auto ptr = la.allocate(256, 1);

        REQUIRE(ptr == buffer);
        REQUIRE(la.capacity() == 0);

        la.reset();
        REQUIRE(la.capacity() == 256);
    }

    SECTION("multiple allocations")
    {
        char buffer[256];
        auto b = cmm::align_forward(buffer, 4);
        auto size = static_cast<int>(buffer + 256 - b);

        cmm::linear_allocator la{{b, size}};

        auto p0 = (char*) la.allocate(9, 1);

        REQUIRE(p0 == b);
        REQUIRE(la.capacity() == size - 9);

        auto p1 = (char*) la.allocate(8, 4);

        REQUIRE(p1 == p0 + 9 + 3);
        REQUIRE(la.capacity() == size - (9 + 3 + 8));

        auto p2 = (char*) la.allocate(4, 2);

        REQUIRE(p2 == p1 + 8);
        REQUIRE(la.capacity() == size - (9 + 3 + 8 + 4));

        auto p3 = (char*) la.allocate(la.capacity(), 2);
        REQUIRE(p3 == p2 + 4);
        REQUIRE(la.capacity() == 0);

        REQUIRE(la.allocate(1, 1) == nullptr);
    }
}
