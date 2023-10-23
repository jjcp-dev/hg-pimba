#ifndef PMB_TILE_SHEET_HPP_GRAMPWJH
#define PMB_TILE_SHEET_HPP_GRAMPWJH

#include <utility>

#include "lgf/texture.hpp"

#include "./rect.hpp"


namespace pmb {

class tile_sheet {
public:

    tile_sheet() = default;

    tile_sheet(const tile_sheet&) = delete;

    tile_sheet(tile_sheet&&) = default;

    tile_sheet(lgf::texture&& texture,
               short tile_width,
               short tile_height,
               short columns,
               short margin=0,
               short spacing=0)
    {
        m_texture = std::move(texture);

        m_tile_width = tile_width;
        m_tile_height = tile_height;
        m_columns = columns;
        m_margin = margin;
        m_spacing = spacing;
    }

    auto operator=(const tile_sheet&)
        -> tile_sheet& = delete;

    auto operator=(tile_sheet&&)
        -> tile_sheet& = default;

    auto operator[] (std::size_t index)
        -> pmb::rect<short>
    {
        short x = index % m_columns;
        short y = index / m_columns;

        short x0 = m_margin + (m_tile_width + m_spacing) * x;
        short y0 = m_margin + (m_tile_height + m_spacing) * y;
        short x1 = x0 + m_tile_width;
        short y1 = y0 + m_tile_height;

        return {x0, y0, x1, y1};
    }

    auto texture() const noexcept
        -> lgf::texture_handle
    {
        return m_texture;
    }

private:

    lgf::texture m_texture;
    short        m_tile_width  = 0;
    short        m_tile_height = 0;
    short        m_margin      = 0;
    short        m_spacing     = 0;
    short        m_columns     = 0;
};

} /* pmb */

#endif
