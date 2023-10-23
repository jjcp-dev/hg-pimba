#ifndef PMB_SPRITE_PARSER_HPP_TLKSKCAH
#define PMB_SPRITE_PARSER_HPP_TLKSKCAH

#include "cmm/span.hpp"

#include "pmb/2d/rect.hpp"


namespace pmb {

class sprite_parser {
public:
    enum {
        version_id      = 0,
        texture_path_id = 1,
        area_id         = 2,
    };

    enum class status {
        success,
        missing_version,
        missing_texture_path,
        missing_area,
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

    auto area() const noexcept
        -> pmb::rect<short>
    {
        return m_area;
    }

private:
    const char*      m_texture_path = nullptr;
    int              m_version = 0;
    pmb::rect<short> m_area;
};

} /* pmb */

#endif
