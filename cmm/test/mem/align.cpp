#include "catch.hpp"
#include "cmm/mem/align.hpp"


TEST_CASE("cmm::forward_alignment_offset()")
{
    SECTION("address == 0")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 0, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 0, 2) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 0, 4) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 0, 8) == 0);
    }

    SECTION("address == 1")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 1, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 1, 2) == 1);
        REQUIRE(cmm::forward_alignment_offset((void*) 1, 4) == 3);
        REQUIRE(cmm::forward_alignment_offset((void*) 1, 8) == 7);
    }

    SECTION("address == 2")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 2, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 2, 2) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 2, 4) == 2);
        REQUIRE(cmm::forward_alignment_offset((void*) 2, 8) == 6);
    }

    SECTION("address == 3")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 3, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 3, 2) == 1);
        REQUIRE(cmm::forward_alignment_offset((void*) 3, 4) == 1);
        REQUIRE(cmm::forward_alignment_offset((void*) 3, 8) == 5);
    }

    SECTION("address == 4")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 4, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 4, 2) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 4, 4) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 4, 8) == 4);
    }

    SECTION("address == 5")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 5, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 5, 2) == 1);
        REQUIRE(cmm::forward_alignment_offset((void*) 5, 4) == 3);
        REQUIRE(cmm::forward_alignment_offset((void*) 5, 8) == 3);
    }

    SECTION("address == 6")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 6, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 6, 2) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 6, 4) == 2);
        REQUIRE(cmm::forward_alignment_offset((void*) 6, 8) == 2);
    }

    SECTION("address == 7")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 7, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 7, 2) == 1);
        REQUIRE(cmm::forward_alignment_offset((void*) 7, 4) == 1);
        REQUIRE(cmm::forward_alignment_offset((void*) 7, 8) == 1);
    }

    SECTION("address == 8")
    {
        REQUIRE(cmm::forward_alignment_offset((void*) 8, 1) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 8, 2) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 8, 4) == 0);
        REQUIRE(cmm::forward_alignment_offset((void*) 8, 8) == 0);
    }
}


TEST_CASE("cmm::align_forward(T*, int)")
{
    SECTION("address == 0")
    {
        REQUIRE(cmm::align_forward((void*) 0, 1) == (void*) 0);
        REQUIRE(cmm::align_forward((void*) 0, 2) == (void*) 0);
        REQUIRE(cmm::align_forward((void*) 0, 4) == (void*) 0);
        REQUIRE(cmm::align_forward((void*) 0, 8) == (void*) 0);
    }

    SECTION("address == 1")
    {
        REQUIRE(cmm::align_forward((void*) 1, 1) == (void*) 1);
        REQUIRE(cmm::align_forward((void*) 1, 2) == (void*) 2);
        REQUIRE(cmm::align_forward((void*) 1, 4) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 1, 8) == (void*) 8);
    }

    SECTION("address == 2")
    {
        REQUIRE(cmm::align_forward((void*) 2, 1) == (void*) 2);
        REQUIRE(cmm::align_forward((void*) 2, 2) == (void*) 2);
        REQUIRE(cmm::align_forward((void*) 2, 4) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 2, 8) == (void*) 8);
    }

    SECTION("address == 3")
    {
        REQUIRE(cmm::align_forward((void*) 3, 1) == (void*) 3);
        REQUIRE(cmm::align_forward((void*) 3, 2) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 3, 4) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 3, 8) == (void*) 8);
    }

    SECTION("address == 4")
    {
        REQUIRE(cmm::align_forward((void*) 4, 1) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 4, 2) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 4, 4) == (void*) 4);
        REQUIRE(cmm::align_forward((void*) 4, 8) == (void*) 8);
    }

    SECTION("address == 5")
    {
        REQUIRE(cmm::align_forward((void*) 5, 1) == (void*) 5);
        REQUIRE(cmm::align_forward((void*) 5, 2) == (void*) 6);
        REQUIRE(cmm::align_forward((void*) 5, 4) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 5, 8) == (void*) 8);
    }

    SECTION("address == 6")
    {
        REQUIRE(cmm::align_forward((void*) 6, 1) == (void*) 6);
        REQUIRE(cmm::align_forward((void*) 6, 2) == (void*) 6);
        REQUIRE(cmm::align_forward((void*) 6, 4) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 6, 8) == (void*) 8);
    }

    SECTION("address == 7")
    {
        REQUIRE(cmm::align_forward((void*) 7, 1) == (void*) 7);
        REQUIRE(cmm::align_forward((void*) 7, 2) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 7, 4) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 7, 8) == (void*) 8);
    }

    SECTION("address == 8")
    {
        REQUIRE(cmm::align_forward((void*) 8, 1) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 8, 2) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 8, 4) == (void*) 8);
        REQUIRE(cmm::align_forward((void*) 8, 8) == (void*) 8);
    }
}


TEST_CASE("cmm::align_backward(T*, int)")
{
    SECTION("address == 0")
    {
        REQUIRE(cmm::align_backward((void*) 0, 1) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 0, 2) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 0, 4) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 0, 8) == (void*) 0);
    }

    SECTION("address == 1")
    {
        REQUIRE(cmm::align_backward((void*) 1, 1) == (void*) 1);
        REQUIRE(cmm::align_backward((void*) 1, 2) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 1, 4) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 1, 8) == (void*) 0);
    }

    SECTION("address == 2")
    {
        REQUIRE(cmm::align_backward((void*) 2, 1) == (void*) 2);
        REQUIRE(cmm::align_backward((void*) 2, 2) == (void*) 2);
        REQUIRE(cmm::align_backward((void*) 2, 4) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 2, 8) == (void*) 0);
    }

    SECTION("address == 3")
    {
        REQUIRE(cmm::align_backward((void*) 3, 1) == (void*) 3);
        REQUIRE(cmm::align_backward((void*) 3, 2) == (void*) 2);
        REQUIRE(cmm::align_backward((void*) 3, 4) == (void*) 0);
        REQUIRE(cmm::align_backward((void*) 3, 8) == (void*) 0);
    }

    SECTION("address == 4")
    {
        REQUIRE(cmm::align_backward((void*) 4, 1) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 4, 2) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 4, 4) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 4, 8) == (void*) 0);
    }

    SECTION("address == 5")
    {
        REQUIRE(cmm::align_backward((void*) 5, 1) == (void*) 5);
        REQUIRE(cmm::align_backward((void*) 5, 2) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 5, 4) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 5, 8) == (void*) 0);
    }

    SECTION("address == 6")
    {
        REQUIRE(cmm::align_backward((void*) 6, 1) == (void*) 6);
        REQUIRE(cmm::align_backward((void*) 6, 2) == (void*) 6);
        REQUIRE(cmm::align_backward((void*) 6, 4) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 6, 8) == (void*) 0);
    }

    SECTION("address == 7")
    {
        REQUIRE(cmm::align_backward((void*) 7, 1) == (void*) 7);
        REQUIRE(cmm::align_backward((void*) 7, 2) == (void*) 6);
        REQUIRE(cmm::align_backward((void*) 7, 4) == (void*) 4);
        REQUIRE(cmm::align_backward((void*) 7, 8) == (void*) 0);
    }

    SECTION("address == 8")
    {
        REQUIRE(cmm::align_backward((void*) 8, 1) == (void*) 8);
        REQUIRE(cmm::align_backward((void*) 8, 2) == (void*) 8);
        REQUIRE(cmm::align_backward((void*) 8, 4) == (void*) 8);
        REQUIRE(cmm::align_backward((void*) 8, 8) == (void*) 8);
    }
}


TEST_CASE("cmm::align_of()")
{
    REQUIRE(cmm::align_of((void*) 0) == 0);
    REQUIRE(cmm::align_of((void*) 1) == 1);
    REQUIRE(cmm::align_of((void*) 2) == 2);
    REQUIRE(cmm::align_of((void*) 3) == 1);
    REQUIRE(cmm::align_of((void*) 4) == 4);
    REQUIRE(cmm::align_of((void*) 5) == 1);
    REQUIRE(cmm::align_of((void*) 6) == 2);
    REQUIRE(cmm::align_of((void*) 7) == 1);
    REQUIRE(cmm::align_of((void*) 8) == 8);
    REQUIRE(cmm::align_of((void*) 9) == 1);
    REQUIRE(cmm::align_of((void*) 10) == 2);
    REQUIRE(cmm::align_of((void*) 11) == 1);
    REQUIRE(cmm::align_of((void*) 12) == 4);
    REQUIRE(cmm::align_of((void*) 13) == 1);
    REQUIRE(cmm::align_of((void*) 14) == 2);
    REQUIRE(cmm::align_of((void*) 15) == 1);
    REQUIRE(cmm::align_of((void*) 16) == 16);

    REQUIRE(cmm::align_of((void*) 0b11101101011000) == 8);
}
