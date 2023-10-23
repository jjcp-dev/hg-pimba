#include "catch.hpp"
#include <cstring>
#include "cmm/jb/writer.hpp"
#include "cmm/jb/parser.hpp"


TEST_CASE("cmm::jb_writer")
{
    SECTION(".write(id, int32)")
    {
        std::uint32_t buffer[2];
        cmm::jb_writer w{buffer};

        REQUIRE(w.write(100, 1234) == true);

        cmm::jb reader{buffer};

        auto v = reader.next();

        REQUIRE(v.id() == 100);
        REQUIRE(v.type() == cmm::jb::type::i32);
        REQUIRE(v.as_int32() == 1234);
    }

    SECTION(".write(id, float)")
    {
        std::uint32_t buffer[2];
        cmm::jb_writer w{buffer};

        REQUIRE(w.write(123, 1.5f) == true);

        cmm::jb reader{buffer};

        auto v = reader.next();

        REQUIRE(v.id() == 123);
        REQUIRE(v.type() == cmm::jb::type::f32);
        REQUIRE(v.as_float() == 1.5f);
    }

    SECTION(".write(id, const char*)")
    {
        std::uint32_t buffer[50];
        cmm::jb_writer w{buffer};

        REQUIRE(w.write(543, "Hola hola") == true);

        cmm::jb reader{buffer};

        auto v = reader.next();

        REQUIRE(v.id() == 543);
        REQUIRE(v.type() == cmm::jb::type::str);
        REQUIRE(v.as_string() == std::string{"Hola hola"});
    }

    SECTION(".write(id, cmm::cspan)")
    {
        std::uint32_t buffer[50];
        cmm::jb_writer w{buffer};

        char msg[] = {'H', 'O', 'L', 'A'};

        REQUIRE(w.write(999, cmm::cspan(msg)) == true);

        cmm::jb reader{buffer};

        auto v = reader.next();

        REQUIRE(v.id() == 999);
        REQUIRE(v.type() == cmm::jb::type::bin);

        auto bin = v.as_binary();

        REQUIRE(bin.size_bytes() == sizeof(msg));
        REQUIRE(std::memcmp(bin.data(), msg, bin.size_bytes()) == 0);
    }

    SECTION(".write(id, cmm::span<int32_t>)")
    {
        std::uint32_t buffer[50];
        std::int32_t numbers[] = {1, 2, 3, 4};
        cmm::jb_writer w{buffer};

        REQUIRE(w.write(111, cmm::make_span(std::as_const(numbers))) == true);

        cmm::jb reader{buffer};

        auto v = reader.next();

        REQUIRE(v.id() == 111);
        REQUIRE(v.type() == cmm::jb::type::i32a);

        auto arr = v.as_int32_array();

        REQUIRE(arr.size() == 4);
        REQUIRE(std::memcmp(arr.data(), numbers, arr.size_bytes()) == 0);
    }
}
