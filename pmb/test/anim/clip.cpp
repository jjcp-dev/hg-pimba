#include "catch.hpp"
#include "pmb/anim/clip.hpp"

#include <chrono>
#include <vector>


using namespace std::chrono_literals;


TEST_CASE("pmb::anim::clip")
{
    SECTION("int16_t & neares interpolation")
    {
        std::vector<std::int16_t> frames({ 0, 1, 2 });
        std::vector<std::chrono::milliseconds> times({ 0ms, 10ms, 20ms });

        pmb::anim::clip c{frames, times, pmb::anim::interpolation::nearest};

        REQUIRE(c.size() == 3);
        REQUIRE(c.duration() == 20ms);
        REQUIRE(c.type() == pmb::anim::frame_type::i16);

        REQUIRE(c.compute_frame<std::int16_t>(0ms) == 0);
        REQUIRE(c.compute_frame<std::int16_t>(5ms) == 0);
        REQUIRE(c.compute_frame<std::int16_t>(9ms) == 1);
        REQUIRE(c.compute_frame<std::int16_t>(10ms) == 1);
        REQUIRE(c.compute_frame<std::int16_t>(15ms) == 1);
        REQUIRE(c.compute_frame<std::int16_t>(19ms) == 2);
        REQUIRE(c.compute_frame<std::int16_t>(20ms) == 2);
    }

    SECTION("int16_t & neares interpolation")
    {
        std::vector<std::int16_t> frames({ 0, 10, 20 });
        std::vector<std::chrono::milliseconds> times({ 0ms, 10ms, 20ms });

        pmb::anim::clip c{frames, times, pmb::anim::interpolation::linear};

        REQUIRE(c.size() == 3);
        REQUIRE(c.duration() == 20ms);
        REQUIRE(c.type() == pmb::anim::frame_type::i16);

        REQUIRE(c.compute_frame<std::int16_t>(0ms) == 0);
        REQUIRE(c.compute_frame<std::int16_t>(5ms) == 5);
        REQUIRE(c.compute_frame<std::int16_t>(10ms) == 10);
        REQUIRE(c.compute_frame<std::int16_t>(15ms) == 15);
        REQUIRE(c.compute_frame<std::int16_t>(20ms) == 20);
    }
}
