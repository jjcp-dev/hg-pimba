#include "catch.hpp"
#include "cmm/jb/parser.hpp"

#include <cstring>
#include <string>


TEST_CASE("cmm::jb")
{
    SECTION("reading an empty buffer")
    {
        cmm::rspan buffer;
        cmm::jb    parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::none);
        REQUIRE(v.id() == 0);
    }

    SECTION("trying to read an invalid buffer")
    {
        std::uint32_t buffer[] = {
            0x01'00'00'01
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::none);
        REQUIRE(v.id() == 0);
    }

    SECTION("reading an int32 value")
    {
        std::uint32_t buffer[] = {
            0x01'00'00'01, 0x00'00'00'FF,
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::i32);
        REQUIRE(v.id() == 1);
        REQUIRE(v.as_int32() == 255);
    }

    SECTION("reading a float value")
    {
        float n = 2.2f;

        std::uint32_t buffer[] = {
            0x02'00'00'0A, *reinterpret_cast<std::uint32_t*>(&n),
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::f32);
        REQUIRE(v.id() == 10);
        REQUIRE(v.as_float() == n);
    }

    SECTION("trying to read an invalid string")
    {
        std::uint32_t buffer[] = {
            0x03'00'00'0C, 10, 0
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::none);
        REQUIRE(v.id() == 0);
    }

    SECTION("reading 0-length string buffer")
    {
        std::uint32_t buffer[] = {
            0x03'00'00'0C, 0
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::str);
        REQUIRE(v.id() == 12);
        REQUIRE(v.as_string() == nullptr);
        REQUIRE(v.as_string_span().data() == nullptr);
        REQUIRE(v.as_string_span().size() == 0);
    }

    SECTION("trying to read a string without null terminator")
    {
        std::uint32_t buffer[] = {
            0x03'00'00'0C, 4, 0x41'41'41'41
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::none);
        REQUIRE(v.id() == 0);
    }

    SECTION("reading a string")
    {
        std::uint32_t buffer[] = {
            0x03'00'00'0C, 5, 0x41'41'41'41, 0
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::str);
        REQUIRE(v.id() == 12);
        REQUIRE(v.as_string() == std::string{"AAAA"});

        REQUIRE(v.as_string_span().data() == v.as_string());
        REQUIRE(v.as_string_span().size_bytes() == 5);
    }

    SECTION("trying to read an invalid binary")
    {
        std::uint32_t buffer[] = {
            0x04'00'00'0C, 10, 0
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::none);
        REQUIRE(v.id() == 0);
    }

    SECTION("reading a 0-length binary buffer")
    {
        std::uint32_t buffer[] = {
            0x04'00'00'0C, 0
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::bin);
        REQUIRE(v.id() == 12);
        REQUIRE(v.as_binary().data() == nullptr);
        REQUIRE(v.as_binary().size_bytes() == 0);
    }

    SECTION("reading a binary")
    {
        std::uint32_t buffer[] = {
            0x04'00'00'0C, 4, 0x41'41'41'41
        };
        cmm::jb parser{buffer};

        auto v = parser.next();

        REQUIRE(v.type() == cmm::jb::type::bin);
        REQUIRE(v.id() == 12);
        REQUIRE(v.as_binary().size_bytes() == 4);
        REQUIRE(std::memcmp(v.as_binary().data(), buffer + 2, 4) == 0);
    }

    SECTION("make sure the buffer is properly aligned")
    {
        SECTION("align after reading a string (length == 4)")
        {
            std::uint32_t buffer[] = {
                0x03'00'00'0C, 4, 0x00'41'41'41,
                0x01'00'00'01, 0x00'00'00'FF,
            };
            cmm::jb parser{buffer};

            auto v0 = parser.next();

            REQUIRE(v0.type() == cmm::jb::type::str);
            REQUIRE(v0.id() == 12);
            REQUIRE(v0.as_string() == std::string{"AAA"});

            REQUIRE(v0.as_string_span().data() == v0.as_string());
            REQUIRE(v0.as_string_span().size_bytes() == 4);

            auto v1 = parser.next();

            REQUIRE(v1.type() == cmm::jb::type::i32);
            REQUIRE(v1.id() == 1);
            REQUIRE(v1.as_int32() == 255);
        }

        SECTION("align after reading a string (length == 5)")
        {
            std::uint32_t buffer[] = {
                0x03'00'00'0C, 5, 0x41'41'41'41, 0,
                0x01'00'00'01, 0x00'00'00'FF,
            };
            cmm::jb parser{buffer};

            auto v0 = parser.next();

            REQUIRE(v0.type() == cmm::jb::type::str);
            REQUIRE(v0.id() == 12);
            REQUIRE(v0.as_string() == std::string{"AAAA"});

            REQUIRE(v0.as_string_span().data() == v0.as_string());
            REQUIRE(v0.as_string_span().size_bytes() == 5);

            auto v1 = parser.next();

            REQUIRE(v1.type() == cmm::jb::type::i32);
            REQUIRE(v1.id() == 1);
            REQUIRE(v1.as_int32() == 255);
        }

        SECTION("align after reading a binary (length == 4)")
        {
            std::uint32_t buffer[] = {
                0x04'00'00'0C, 4, 0x41'41'41'41,
                0x01'00'00'01, 0x00'00'00'FF,
            };
            cmm::jb parser{buffer};

            auto v0 = parser.next();

            REQUIRE(v0.type() == cmm::jb::type::bin);
            REQUIRE(v0.id() == 12);
            REQUIRE(v0.as_binary().size_bytes() == 4);
            REQUIRE(std::memcmp(v0.as_binary().data(), buffer + 2, 4) == 0);

            auto v1 = parser.next();

            REQUIRE(v1.type() == cmm::jb::type::i32);
            REQUIRE(v1.id() == 1);
            REQUIRE(v1.as_int32() == 255);
        }

        SECTION("align after reading a binary (length == 5)")
        {
            std::uint32_t buffer[] = {
                0x04'00'00'0C, 5, 0x41'41'41'41, 0x41'00'00'00,
                0x01'00'00'01, 0x00'00'00'FF,
            };
            cmm::jb parser{buffer};

            auto v0 = parser.next();

            REQUIRE(v0.type() == cmm::jb::type::bin);
            REQUIRE(v0.id() == 12);
            REQUIRE(v0.as_binary().size_bytes() == 5);
            REQUIRE(std::memcmp(v0.as_binary().data(), buffer + 2, 5) == 0);

            auto v1 = parser.next();

            REQUIRE(v1.type() == cmm::jb::type::i32);
            REQUIRE(v1.id() == 1);
            REQUIRE(v1.as_int32() == 255);
        }
    }
}
