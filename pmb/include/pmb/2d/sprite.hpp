#ifndef PMB_2D_SPRITE_HPP_OR0DVSWT
#define PMB_2D_SPRITE_HPP_OR0DVSWT

#include <cassert>
#include <cstdint>
#include <limits>

#include "lgf/texture.hpp"

#include "./rect.hpp"


namespace pmb {

namespace details {

    inline auto compute_uvs(int width, int height, pmb::rect<short> region)
        -> pmb::rect<unsigned short>
    {
        assert(width >= 0 and width <= std::numeric_limits<short>::max());
        assert(height >= 0 and height <= std::numeric_limits<short>::max());

        assert(region.x0 >= 0 and region.x0 <= width);
        assert(region.y0 >= 0 and region.y0 <= height);
        assert(region.x1 >= 0 and region.x1 <= width);
        assert(region.y1 >= 0 and region.y1 <= height);

        const auto max = std::numeric_limits<unsigned short>::max();

        return {
            static_cast<unsigned short>(max * (region.x0 / float(width))),
            static_cast<unsigned short>(max * (region.y0 / float(height))),
            static_cast<unsigned short>(max * (region.x1 / float(width))),
            static_cast<unsigned short>(max * (region.y1 / float(height)))
        };
    }

} /* details */


class sprite {
public:

    sprite() = default;

    sprite(lgf::texture_handle texture,
           short width, short height, pmb::rect<short> region)
    {
        m_texture = texture;
        m_width = width;
        m_height = height;
        m_uvs = pmb::details::compute_uvs(
            texture.width(), texture.height(), region);
    }

    sprite(lgf::texture_handle texture, pmb::rect<short> region)
        : sprite(texture, region.x1 - region.x0, region.y1 - region.y0, region)
    { }

    auto texture() const noexcept
        -> lgf::texture_handle
    {
        return m_texture;
    }

    auto uvs() const noexcept
        -> pmb::rect<std::uint16_t>
    {
        return m_uvs;
    }

    auto width() const noexcept
        -> short
    {
        return m_width;
    }

    auto height() const noexcept
        -> short
    {
        return m_height;
    }

private:
    lgf::texture_handle      m_texture;
    pmb::rect<std::uint16_t> m_uvs;
    short                    m_width = 0;
    short                    m_height = 0;
};

} /* pmb */

#endif
