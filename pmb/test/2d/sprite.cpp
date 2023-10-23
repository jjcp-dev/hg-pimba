#include "catch.hpp"
#include "pmb/2d/sprite.hpp"


TEST_CASE("pmb::details::compute_uvs()")
{
    auto uvs = pmb::details::compute_uvs(256, 256, {0, 0, 256, 256});

    REQUIRE(uvs.x0 == 0);
    REQUIRE(uvs.y0 == 0);
    REQUIRE(uvs.x1 == std::numeric_limits<unsigned short>::max());
    REQUIRE(uvs.y1 == std::numeric_limits<unsigned short>::max());
}


TEST_CASE("pmb::sprite")
{
    // TODO: ...
}
