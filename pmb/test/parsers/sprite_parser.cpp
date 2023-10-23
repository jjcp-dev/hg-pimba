#include <cstdint>

#include "catch.hpp"

#include "cmm/jb/writer.hpp"
#include "pmb/parsers/sprite_parser.hpp"


TEST_CASE("pmb::sprite_parser")
{
    SECTION("parsing an empty buffer should fail")
    {
        pmb::sprite_parser p;

        REQUIRE(p.parse({}) != pmb::sprite_parser::status::success);
    }

    SECTION("should return status::missing_version")
    {
        std::uint32_t buffer[50];
        cmm::jb_writer writer{buffer};

        writer.write(pmb::sprite_parser::texture_path_id, "texture/path");

        pmb::sprite_parser p;
        auto status = p.parse(buffer);

        REQUIRE(status == pmb::sprite_parser::status::missing_version);
    }

    SECTION("should return status::missing_texture_path")
    {
        std::uint32_t buffer[50];
        cmm::jb_writer writer{buffer};

        writer.write(pmb::sprite_parser::version_id, 0);

        pmb::sprite_parser p;
        auto status = p.parse(buffer);

        REQUIRE(status == pmb::sprite_parser::status::missing_texture_path);
    }

    SECTION("should succeed given a properly formatted buffer")
    {
        std::uint32_t buffer[50];
        cmm::jb_writer writer{buffer};

        writer.write(pmb::sprite_parser::version_id, 10);
        writer.write(pmb::sprite_parser::texture_path_id, "texture/path");

        pmb::sprite_parser p;
        auto status = p.parse(buffer);

        REQUIRE(status == pmb::sprite_parser::status::success);
        REQUIRE(p.texture_path() == std::string{"texture/path"});
        REQUIRE(p.version() == 10);
    }

    SECTION("should ignore unknown fields")
    {
        std::uint32_t buffer[50];
        cmm::jb_writer writer{buffer};

        writer.write(100, 1234);
        writer.write(pmb::sprite_parser::version_id, 10);
        writer.write(101, "Hola");
        writer.write(pmb::sprite_parser::texture_path_id, "texture/path");
        writer.write(102, 4.5f);

        pmb::sprite_parser p;
        auto status = p.parse(buffer);

        REQUIRE(status == pmb::sprite_parser::status::success);
        REQUIRE(p.texture_path() == std::string{"texture/path"});
        REQUIRE(p.version() == 10);
    }
}
