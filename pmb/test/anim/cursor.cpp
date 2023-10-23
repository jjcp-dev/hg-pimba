#include "catch.hpp"
#include "pmb/anim/cursor.hpp"

#include <chrono>


using namespace std::chrono_literals;


TEST_CASE("pmb::anim::cursor")
{
    SECTION("default constructed animation cursor")
    {
        pmb::anim::cursor ac;

        REQUIRE(ac.duration() == 0ms);
        REQUIRE(ac.current() == 0ms);
        REQUIRE(ac.loop_mode() == pmb::anim::loop_mode::single);
        REQUIRE(ac.direction() == 1);

        ac.advance(0ms);
        REQUIRE(ac.current() == 0ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 0ms);
    }

    SECTION("single")
    {
        pmb::anim::cursor ac{10ms, pmb::anim::loop_mode::single};

        REQUIRE(ac.duration() == 10ms);
        REQUIRE(ac.current() == 0ms);
        REQUIRE(ac.loop_mode() == pmb::anim::loop_mode::single);
        REQUIRE(ac.direction() == 1);

        ac.advance(0ms);
        REQUIRE(ac.current() == 0ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 5ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 10ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 10ms);
    }

    SECTION("repeat")
    {
        pmb::anim::cursor ac{10ms, pmb::anim::loop_mode::repeat};

        REQUIRE(ac.duration() == 10ms);
        REQUIRE(ac.current() == 0ms);
        REQUIRE(ac.loop_mode() == pmb::anim::loop_mode::repeat);
        REQUIRE(ac.direction() == 1);

        ac.advance(0ms);
        REQUIRE(ac.current() == 0ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 5ms);

        ac.advance(4ms);
        REQUIRE(ac.current() == 9ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 4ms);
    }

    SECTION("bounce")
    {
        pmb::anim::cursor ac{10ms, pmb::anim::loop_mode::bounce};

        REQUIRE(ac.duration() == 10ms);
        REQUIRE(ac.current() == 0ms);
        REQUIRE(ac.loop_mode() == pmb::anim::loop_mode::bounce);
        REQUIRE(ac.direction() == 1);

        ac.advance(0ms);
        REQUIRE(ac.current() == 0ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 5ms);

        ac.advance(4ms);
        REQUIRE(ac.current() == 9ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 6ms);
        REQUIRE(ac.direction() == -1);

        ac.advance(5ms);
        REQUIRE(ac.current() == 1ms);

        ac.advance(5ms);
        REQUIRE(ac.current() == 4ms);
        REQUIRE(ac.direction() == 1);
    }
}
