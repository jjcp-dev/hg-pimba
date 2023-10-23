#include "pmb/parsers/sprite_sheet_parser.hpp"

#include "cmm/jb/parser.hpp"


auto pmb::sprite_sheet_parser::parse(cmm::rspan buffer) noexcept
    -> status
{
    cmm::jb parser{buffer};

    bool has_version      = false;
    bool has_texture_path = false;
    bool has_sprites      = false;

    parser.for_each([&] (const auto& v) {
        if (v.id() == version_id and v.type() == cmm::jb::type::i32)
        {
            has_version = true;

            m_version = v.as_int32();
        }
        else if (v.id() == texture_path_id and v.type() == cmm::jb::type::str)
        {
            has_texture_path = true;

            m_texture_path = v.as_string();
        }
        else if (v.id() == sprites_id and v.type() == cmm::jb::type::bin)
        {
            auto sprites = v.as_binary();

            if (sprites.size_bytes() % sizeof(std::int16_t) == 0)
            {
                has_sprites = true;

                auto size = static_cast<int>(
                    sprites.size_bytes() / sizeof(std::int16_t));

                m_sprites = {(short*) sprites.data(), size};
            }
        }
    });

    if (not has_version)
        return status::missing_version;

    if (not has_texture_path)
        return status::missing_texture_path;

    if (not has_sprites)
        return status::missing_sprites;

    return status::success;
}

