#include "pmb/parsers/sprite_parser.hpp"

#include "cmm/jb/parser.hpp"


auto pmb::sprite_parser::parse(cmm::rspan buffer) noexcept
    -> status
{
    cmm::jb parser{buffer};

    bool has_version      = false;
    bool has_texture_path = false;
    // bool has_area = false;

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
    });

    if (not has_version)
        return status::missing_version;

    if (not has_texture_path)
        return status::missing_texture_path;

    return status::success;
}

