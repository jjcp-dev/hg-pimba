#ifndef PMB_TILESET_HPP_VBV3OFDJ
#define PMB_TILESET_HPP_VBV3OFDJ

#include <utility>
#include <vector>

#include "lgf/texture.hpp"

#include "pmb/2d/rect.hpp"


namespace pmb {
namespace details {

    struct homogeneous_tileset {
        short tile_width  = 0;
        short tile_height = 0;
        short margin      = 0;
        short spacing     = 0;
        short columns     = 0;
    };

    struct heterogeneous_tileset {
        std::vector<pmb::rect<short>> sprites;
    };

} /* details */


class tileset {
public:

    tileset()
    {
        new (&m_homogeneous) pmb::details::homogeneous_tileset{};
    }

    tileset(const tileset&) = delete;

    tileset(tileset&& ts)
    {
        m_texture = std::move(ts.m_texture);

        if (ts.m_is_homogeneous)
            new (&m_homogeneous) pmb::details::homogeneous_tileset{
                std::move(ts.m_homogeneous)};
        else
            new (&m_heterogeneous) pmb::details::heterogeneous_tileset{
                std::move(ts.m_heterogeneous)};

        m_is_homogeneous = ts.m_is_homogeneous;
    }

    tileset(lgf::texture&& texture,
            short tile_width,
            short tile_height,
            short columns,
            short margin=0,
            short spacing=0)
    {
        m_texture = std::move(texture);

        new (&m_homogeneous) pmb::details::homogeneous_tileset{};
        m_is_homogeneous = true;

        m_homogeneous.tile_width = tile_width;
        m_homogeneous.tile_height = tile_height;
        m_homogeneous.columns = columns;
        m_homogeneous.margin = margin;
        m_homogeneous.spacing = spacing;
    }

   ~tileset()
    {
        if (m_is_homogeneous)
            m_homogeneous.~homogeneous_tileset();
        else
            m_heterogeneous.~heterogeneous_tileset();
    }

    auto operator=(const tileset&)
        -> tileset& = delete;

    // auto operator=(tileset&&)
    //     -> tileset& = default;

    auto operator[] (std::size_t index) const noexcept
        -> pmb::rect<short>
    {
        if (m_is_homogeneous)
        {
            short x = index % m_homogeneous.columns;
            short y = index / m_homogeneous.columns;

            short x0 = m_homogeneous.margin
                     + (m_homogeneous.tile_width + m_homogeneous.spacing) * x;
            short y0 = m_homogeneous.margin
                     + (m_homogeneous.tile_height + m_homogeneous.spacing) * y;
            short x1 = x0 + m_homogeneous.tile_width;
            short y1 = y0 + m_homogeneous.tile_height;

            return {x0, y0, x1, y1};
        }
        else
        {
            return m_heterogeneous.sprites[index];
        }
    }

    auto texture() const noexcept
        -> lgf::texture_handle
    {
        return m_texture;
    }

    auto is_homogeneous() const noexcept
        -> bool
    {
        return m_is_homogeneous;
    }

private:

    lgf::texture m_texture;
    union {
        pmb::details::homogeneous_tileset   m_homogeneous;
        pmb::details::heterogeneous_tileset m_heterogeneous;
    };
    bool m_is_homogeneous = true;
};

} /* pmb */

#endif
