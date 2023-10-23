#include "catch.hpp"
#include "lgf/vtx_buffer.hpp"

#include "./test_context.hpp"


auto context = lgf::test_context{};


TEST_CASE("lgf::vtx_buffer")
{
    SECTION("create and populate static vtx_buffer without initial data")
    {
        auto decl   = lgf::vtx_decl{{2, lgf::vtx_decl::type::f32}};
        auto usage  = lgf::vtx_usage::static_draw;
        auto buffer = lgf::vtx_buffer{usage, decl, 6};

        struct vertex {
            float x, y;
        };

        REQUIRE(buffer.usage() == usage);
        REQUIRE(buffer.decl() == decl);

        auto mapped = buffer.map(lgf::buffer_access::write);

        REQUIRE(mapped.data() != nullptr);
        REQUIRE(mapped.size() == 6 * decl.stride());
        REQUIRE(mapped.size_bytes() == mapped.size());

        auto ptr = reinterpret_cast<vertex*>(mapped.data());

        ptr[0] = {0.0f, 0.0f};
        ptr[1] = {1.0f, 2.0f};
        ptr[2] = {3.0f, 4.0f};
        ptr[3] = {5.0f, 6.0f};
        ptr[4] = {7.0f, 8.0f};
        ptr[5] = {9.0f, 0.0f};

        buffer.unmap();

        SECTION("make sure the data was properly written")
        {
            auto mapped = buffer.map(lgf::buffer_access::read);

            REQUIRE(mapped.data() != nullptr);
            REQUIRE(mapped.size() == 6 * decl.stride());

            auto ptr = reinterpret_cast<vertex*>(mapped.data());

            REQUIRE(ptr[0].x == 0.0f); REQUIRE(ptr[0].y == 0.0f);
            REQUIRE(ptr[1].x == 1.0f); REQUIRE(ptr[1].y == 2.0f);
            REQUIRE(ptr[2].x == 3.0f); REQUIRE(ptr[2].y == 4.0f);
            REQUIRE(ptr[3].x == 5.0f); REQUIRE(ptr[3].y == 6.0f);
            REQUIRE(ptr[4].x == 7.0f); REQUIRE(ptr[4].y == 8.0f);
            REQUIRE(ptr[5].x == 9.0f); REQUIRE(ptr[5].y == 0.0f);
        }
    }

    SECTION("create and populate static vtx_buffer with initial data")
    {
        struct vertex {
            float x, y;
        };

        vertex data[] = {
            {0.0f, 0.0f},
            {1.0f, 2.0f},
            {3.0f, 4.0f},
            {5.0f, 6.0f},
            {7.0f, 8.0f},
            {9.0f, 0.0f},
        };

        auto decl   = lgf::vtx_decl{{2, lgf::vtx_decl::type::f32}};
        auto usage  = lgf::vtx_usage::static_draw;
        auto buffer = lgf::vtx_buffer{usage, decl, data};

        REQUIRE(buffer.usage() == usage);
        REQUIRE(buffer.decl() == decl);

        auto mapped = buffer.map(lgf::buffer_access::read);

        REQUIRE(mapped.data() != nullptr);
        REQUIRE(mapped.size() == 6 * decl.stride());

        auto ptr = reinterpret_cast<vertex*>(mapped.data());

        REQUIRE(ptr[0].x == 0.0f); REQUIRE(ptr[0].y == 0.0f);
        REQUIRE(ptr[1].x == 1.0f); REQUIRE(ptr[1].y == 2.0f);
        REQUIRE(ptr[2].x == 3.0f); REQUIRE(ptr[2].y == 4.0f);
        REQUIRE(ptr[3].x == 5.0f); REQUIRE(ptr[3].y == 6.0f);
        REQUIRE(ptr[4].x == 7.0f); REQUIRE(ptr[4].y == 8.0f);
        REQUIRE(ptr[5].x == 9.0f); REQUIRE(ptr[5].y == 0.0f);
    }
}
