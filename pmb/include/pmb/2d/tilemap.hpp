#ifndef PMB_2D_TILEMAP_HPP_6BSNDALH
#define PMB_2D_TILEMAP_HPP_6BSNDALH

#include <cstdint>

#include <vector>

#include "cmm/span.hpp"

#include "./sprite_sheet.hpp"
#include "./sprite_batcher.hpp"
#include "./tile_sheet.hpp"


namespace pmb {

class tilemap {
public:
    using tile_type = std::uint16_t;

    auto operator[] (std::size_t index) noexcept
        -> cmm::span<tile_type>
    {
        const auto length = (int) m_block_width * m_block_height;

        return {&m_map[length * index], length};
    }

    void prep()
    {
        // m_batcher = pmb::sprite_batcher{(int) m_map.size()};

        m_batcher.begin();

        for (int i = 0; i < (int) m_map.size(); i++)
        {
            auto x = i % m_columns;
            auto y = i / m_columns;

            auto sprite = m_sheet[i];

            m_batcher.add(sprite, {x * sprite.width(), y * sprite.height()}, 0);
            // m_batcher.add({x, y}, 16, 16, {0, 0, 65535, 65535}, 0);
        }

        m_batcher.end();
    }

    pmb::sprite_batcher    m_batcher;
    pmb::tile_sheet        m_tile_sheet;
    pmb::sprite_sheet      m_sheet;
    std::vector<tile_type> m_map;
    int                    m_block_width  = 1;
    int                    m_block_height = 1;
    int                    m_columns      = 0;
    int                    m_rows         = 0;
};

} /* pmb */

#endif
