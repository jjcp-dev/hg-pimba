#ifndef PMB_2D_TILE_CALC_HPP_YQ410GDA
#define PMB_2D_TILE_CALC_HPP_YQ410GDA

#include "./rect.hpp"


namespace pmb {

inline auto compute_tile_coords(int index,
                                int tile_width,
                                int tile_height,
                                int columns,
                                int margin=0,
                                int spacing=0) noexcept
    -> pmb::rect<int>
{
    auto x = index % columns;
    auto y = index / columns;

    auto x0 = margin + (tile_width + spacing) * x;
    auto y0 = margin + (tile_height + spacing) * y;
    auto x1 = x0 + tile_width;
    auto y1 = y0 + tile_height;

    return {x0, y0, x1, y1};
}

} /* pmb */

#endif
