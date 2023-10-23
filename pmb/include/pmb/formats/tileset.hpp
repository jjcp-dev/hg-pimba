#ifndef PMB_TOOLS_PARSERS_TILESET_HPP_SRHWJ9CK
#define PMB_TOOLS_PARSERS_TILESET_HPP_SRHWJ9CK

#include <ostream>

#include "cmm/result.hpp"
#include "cmm/span.hpp"


namespace pmb {
namespace fmt {

struct tileset_data {
    const char* image       = "";
    int         columns     = 0;
    int         tile_width  = 0;
    int         tile_height = 0;
    int         spacing     = 0;
};


enum class tileset_attribute_id {
    image       = 0,
    columns     = 1,
    tile_width  = 2,
    tile_height = 3,
    spacing     = 4,
};


enum class tileset_error {
    missing_image,
    missing_columns,
    missing_tile_width,
    missing_tile_height,
    missing_spacing,
};


auto parse_tileset(cmm::cspan buffer) noexcept
    -> cmm::result<pmb::fmt::tileset_data,
                   pmb::fmt::tileset_error>;


auto write_tileset(const pmb::fmt::tileset_data& ts,
                   cmm::rspan                    output_buffer) noexcept
    -> cmm::rspan;

} /* fmt */
} /* pmb */

#endif
