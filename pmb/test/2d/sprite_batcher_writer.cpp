#include "catch.hpp"
#include "pmb/2d/sprite_batcher.hpp"

#include <cstring>
#include <vector>


using quad = pmb::sprite_batcher_writer::quad;


bool operator== (const quad& a, const quad& b)
{
    return std::memcmp(&a, &b, sizeof(quad)) == 0;
}


TEST_CASE("pmb::spriter_batcher_writer")
{
    std::vector<quad> v;
    v.resize(10);

    pmb::sprite_batcher_writer sbw{{v}};

    REQUIRE(sbw.span().data() == v.data());
    REQUIRE(sbw.span().size() == 0);

    REQUIRE(sbw.add({0.f, 0.f}, 16, 16, {0, 0, 100, 100}, 0) == true);

    REQUIRE(sbw.span().size() == 1);
    REQUIRE(sbw.span()[0] == quad{
        { 0.0f,  0.0f,   0,   0, 0}, // top-left
        { 0.0f, 16.0f,   0, 100, 0}, // bottom-left
        {16.0f, 16.0f, 100, 100, 0}, // bottom-right
        { 0.0f,  0.0f,   0,   0, 0}, // top-left
        {16.0f, 16.0f, 100, 100, 0}, // bottom-right
        {16.0f,  0.0f, 100,   0, 0}, // top-right
    });

    REQUIRE(sbw.add({10.f, 5.f}, 16, 16, {0, 0, 100, 100}, 1) == true);

    REQUIRE(sbw.span().size() == 2);
    REQUIRE(sbw.span()[1] == quad{
        {10 +  0.0f, 5 +  0.0f,   0,   0, 1}, // top-left
        {10 +  0.0f, 5 + 16.0f,   0, 100, 1}, // bottom-left
        {10 + 16.0f, 5 + 16.0f, 100, 100, 1}, // bottom-right
        {10 +  0.0f, 5 +  0.0f,   0,   0, 1}, // top-left
        {10 + 16.0f, 5 + 16.0f, 100, 100, 1}, // bottom-right
        {10 + 16.0f, 5 +  0.0f, 100,   0, 1}, // top-right
    });

    REQUIRE(sbw.add({20.f, 8.f}, 16, 32, {20, 30, 40, 50}, 2) == true);

    REQUIRE(sbw.span().size() == 3);
    REQUIRE(sbw.span()[2] == quad{
        {20 +  0.0f, 8 +  0.0f, 20, 30, 2}, // top-left
        {20 +  0.0f, 8 + 32.0f, 20, 50, 2}, // bottom-left
        {20 + 16.0f, 8 + 32.0f, 40, 50, 2}, // bottom-right
        {20 +  0.0f, 8 +  0.0f, 20, 30, 2}, // top-left
        {20 + 16.0f, 8 + 32.0f, 40, 50, 2}, // bottom-right
        {20 + 16.0f, 8 +  0.0f, 40, 30, 2}, // top-right
    });
}
