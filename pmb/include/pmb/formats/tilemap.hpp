#ifndef PMB_TILEMAP_HPP_REX3CSB1
#define PMB_TILEMAP_HPP_REX3CSB1

#include <vector>
#include "cmm/span.hpp"
#include "cmm/result.hpp"


namespace pmb {
namespace fmt {

struct tilemap_data {
    struct layer {
        const char*            tileset     = "";
        int                    columns     = 0;
        int                    rows        = 0;
        cmm::span<const short> map;
    };

    std::vector<layer> layers;
};


enum class tilemap_attribute_id {
    tileset,
    columns,
    rows,
    map,
};


enum class tilemap_error {
    missing_tileset,
    missing_columns,
    missing_rows,
    missing_map,
};


auto parse_tilemap(cmm::cspan buffer) noexcept
    -> cmm::result<pmb::fmt::tilemap_data,
                   pmb::fmt::tilemap_error>;


auto write_tilemap(const pmb::fmt::tilemap_data& ts,
                   cmm::rspan                    output_buffer) noexcept
    -> cmm::rspan;

} /* fmt */
} /* pmb */

#endif
