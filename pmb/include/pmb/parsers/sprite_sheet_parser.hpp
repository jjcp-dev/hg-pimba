#ifndef PMB_SPRITE_SHEET_PARSER_HPP_UV5T4OGX
#define PMB_SPRITE_SHEET_PARSER_HPP_UV5T4OGX

#include <type_traits>

#include "cmm/span.hpp"

#include "pmb/2d/rect.hpp"


namespace pmb {

class sprite_sheet_parser {
public:
    enum {
        version_id      = 0,
        texture_path_id = 1,
        sprites_id      = 2,
    };

    enum class status {
        success,
        missing_version,
        missing_texture_path,
        missing_sprites,
    };

    auto parse(cmm::rspan) noexcept
        -> status;

    auto version() const noexcept
        -> int
    {
        return m_version;
    }

    auto texture_path() const noexcept
        -> const char*
    {
        return m_texture_path;
    }

private:

    const char*      m_texture_path = nullptr;
    int              m_version = 0;
    cmm::span<short> m_sprites;
};

} /* pmb */

#endif
