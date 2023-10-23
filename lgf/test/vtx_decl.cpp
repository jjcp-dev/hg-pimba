#include "catch.hpp"
#include "lgf/vtx_decl.hpp"


TEST_CASE("lgf::vtx_decl::slot")
{
    lgf::vtx_decl::slot s0{1, false, lgf::vtx_decl::type::i16};
    lgf::vtx_decl::slot s1{1, true, lgf::vtx_decl::type::i8};
    lgf::vtx_decl::slot s2{2, lgf::vtx_decl::type::i16};
    lgf::vtx_decl::slot s3{3, true, lgf::vtx_decl::type::f32};
    lgf::vtx_decl::slot s4{3, true, lgf::vtx_decl::type::f32};

    REQUIRE(s0.count() == 1);
    REQUIRE(s0.normalized() == false);
    REQUIRE(s0.type() == lgf::vtx_decl::type::i16);

    REQUIRE(s1.count() == 1);
    REQUIRE(s1.normalized() == true);
    REQUIRE(s1.type() == lgf::vtx_decl::type::i8);

    REQUIRE(s2.count() == 2);
    REQUIRE(s2.normalized() == false);
    REQUIRE(s2.type() == lgf::vtx_decl::type::i16);

    REQUIRE(s3.count() == 3);
    REQUIRE(s3.normalized() == true);
    REQUIRE(s3.type() == lgf::vtx_decl::type::f32);

    REQUIRE(s4.count() == 3);
    REQUIRE(s4.normalized() == true);
    REQUIRE(s4.type() == lgf::vtx_decl::type::f32);

    REQUIRE(s0 != s1);
    REQUIRE(s0 != s2);
    REQUIRE(s0 != s3);
    REQUIRE(not (s3 != s4));

    REQUIRE(not (s0 == s1));
    REQUIRE(not (s0 == s2));
    REQUIRE(not (s0 == s3));
    REQUIRE(s3 == s4);
}


TEST_CASE("lgf::vtx_decl")
{
    SECTION("empty vtx_decl")
    {
        lgf::vtx_decl vd;

        REQUIRE(vd.stride() == 0);
        REQUIRE(vd.size() == 0);
        REQUIRE(vd.begin() == vd.end());
        REQUIRE(vd.cbegin() == vd.cend());

        REQUIRE(vd == lgf::vtx_decl{});
        REQUIRE(not (vd != lgf::vtx_decl{}));
    }

    SECTION("vtx_decl with 1 item")
    {
        auto vd = lgf::vtx_decl{
            {4, lgf::vtx_decl::type::f32},
        };

        REQUIRE(std::distance(vd.begin(), vd.end()) == 1);
        REQUIRE(std::distance(vd.cbegin(), vd.cend()) == 1);

        REQUIRE(vd.stride() == 4 * sizeof(float));
        REQUIRE(vd.size() == 1);

        REQUIRE(vd[0] == lgf::vtx_decl::slot{4, lgf::vtx_decl::type::f32});

        SECTION("comparison operators")
        {
            auto vd2 = lgf::vtx_decl{
                {4, lgf::vtx_decl::type::f32},
            };

            REQUIRE(vd == vd2);
            REQUIRE(not (vd != vd2));

            auto vd3 = lgf::vtx_decl{
                {3, lgf::vtx_decl::type::f32},
            };

            REQUIRE(vd != vd3);
            REQUIRE(not (vd == vd3));

            auto vd4 = lgf::vtx_decl{
                {3, lgf::vtx_decl::type::f32},
                {1, lgf::vtx_decl::type::f32},
            };

            REQUIRE(vd != lgf::vtx_decl{});
            REQUIRE(vd != vd4);
            REQUIRE(not (vd == vd4));
        }
    }

    SECTION("vtx_decl with 4 items")
    {
        auto vd = lgf::vtx_decl{
            {4, lgf::vtx_decl::type::f32},
            {2, lgf::vtx_decl::type::u8},
            {1, lgf::vtx_decl::type::none},
            {1, lgf::vtx_decl::type::i16},
        };

        REQUIRE(std::distance(vd.begin(), vd.end()) == 4);
        REQUIRE(std::distance(vd.cbegin(), vd.cend()) == 4);

        REQUIRE(vd.stride() == (4 * 4 + 2 * 1 + 1 * 0 + 1 * 2));

        REQUIRE(vd.size() == 4);
        REQUIRE(vd[0] == lgf::vtx_decl::slot{4, lgf::vtx_decl::type::f32});
        REQUIRE(vd[1] == lgf::vtx_decl::slot{2, lgf::vtx_decl::type::u8});
        REQUIRE(vd[2] == lgf::vtx_decl::slot{1, lgf::vtx_decl::type::none});
        REQUIRE(vd[3] == lgf::vtx_decl::slot{1, lgf::vtx_decl::type::i16});

        SECTION("comparison operators")
        {
            auto vd2 = lgf::vtx_decl{
                {4, lgf::vtx_decl::type::f32},
                {2, lgf::vtx_decl::type::u8},
                {1, lgf::vtx_decl::type::none},
                {1, lgf::vtx_decl::type::i16},
            };

            REQUIRE(vd == vd2);
            REQUIRE(not (vd != vd2));

            auto vd3 = lgf::vtx_decl{
                {4, lgf::vtx_decl::type::f32},
                {2, lgf::vtx_decl::type::u8},
                {1, lgf::vtx_decl::type::none},
                {1, lgf::vtx_decl::type::f32},
            };

            REQUIRE(vd != vd3);
            REQUIRE(not (vd == vd3));

            auto vd4 = lgf::vtx_decl{
                {4, lgf::vtx_decl::type::f32},
                {2, lgf::vtx_decl::type::u8},
            };

            REQUIRE(vd != vd4);
            REQUIRE(not (vd == vd4));
        }
    }
}
