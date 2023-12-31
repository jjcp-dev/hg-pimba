#ifndef PMBC_TILED_HPP_8ZIOMENX
#define PMBC_TILED_HPP_8ZIOMENX

#include <string>
#include <cstdint>

#include "nlohmann/json.hpp"

#include "cmm/result.hpp"


namespace pmbc {

struct tiled_tileset {
    std::string type;
    std::string name;
    std::string image;
    int         columns     = 0;
    int         imageheight = 0;
    int         imagewidth  = 0;
    int         margin      = 0;
    int         spacing     = 0;
    int         tilecount   = 0;
    int         tileheight  = 0;
    int         tilewidth   = 0;
};


/**
 * @brief All possible errors while parsing a Tiled tileset file
 */
enum class tiled_tileset_error {
    wrong_type,
    missing_name,
    missing_image,
    missing_imageheight,
    missing_imagewidth,
    missing_columns,
    missing_margin,
    missing_spacing,
    missing_tilecount,
    missing_tileheight,
    missing_tilewidth,
};


/**
 * @brief Parse a JSON tileset generated by Tiled.
 *
 * @param tiled_json A json object to parse
 *
 * @return Either a pmbc::tiled_tileset or a pmbc::tiled_tileset_error
 */
auto read_tiled_tileset(const nlohmann::json& tiled_json)
    -> cmm::result<pmbc::tiled_tileset, pmbc::tiled_tileset_error>;


/**
 * @brief Get a string representation of a pmbc::tiled_tileset_error
 *
 * @param err The value to convert
 *
 * @return The string representation of `err` (statically allocated)
 */
auto err_to_str(pmbc::tiled_tileset_error err)
    -> const char*;


struct tiled_tilemap {
    std::uint32_t background_color = 0; // AARRGGBB
    bool          infinite         = false;
    int           height           = 0; // Number of rows
    int           width            = 0; // Number of columns
    int           tile_height      = 0;
    int           tile_width       = 0;
};


/**
 * @brief All possible errors while parsing a Tiled tileset file
 */
enum class tiled_tilemap_error {
    wrong_type,
    missing_name,
    missing_image,
    missing_imageheight,
    missing_imagewidth,
    missing_columns,
    missing_margin,
    missing_spacing,
    missing_tilecount,
    missing_tileheight,
    missing_tilewidth,
};


/**
 */
auto read_tiled_tilemap(const nlohmann::json& tiled_json)
    -> cmm::result<pmbc::tiled_tilemap, pmbc::tiled_tilemap_error>;

} /* pmbc */

#endif
