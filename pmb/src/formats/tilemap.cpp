#include "pmb/formats/tilemap.hpp"

#include "cmm/jb/parser.hpp"
#include "cmm/jb/writer.hpp"


auto pmb::fmt::parse_tilemap(cmm::cspan buffer) noexcept
    -> cmm::result<pmb::fmt::tilemap_data,
                   pmb::fmt::tilemap_error>
{
    auto parser = cmm::jb{buffer};

    pmb::fmt::tilemap_data tilemap;

    bool read_tileset = false;
    bool read_columns = false;
    bool read_rows = false;
    bool read_map = false;

    parser.for_each([&] (const cmm::jb::value& value) {
        switch (value.id()) {
        case int(pmb::fmt::tilemap_attribute_id::tileset):
            if (value.type() == cmm::jb::type::str)
            {
                tilemap.tileset = value.as_string();
                read_tileset = true;
            }
            break;

            case int(pmb::fmt::tilemap_attribute_id::columns):
            if (value.type() == cmm::jb::type::i32)
            {
                tilemap.columns = value.as_int32();
                read_columns = true;
            }
            break;

            case int(pmb::fmt::tilemap_attribute_id::rows):
            if (value.type() == cmm::jb::type::i32)
            {
                tilemap.rows = value.as_int32();
                read_rows = true;
            }
            break;

            case int(pmb::fmt::tilemap_attribute_id::map):
            // if (value.type() == cmm::jb::type::i32)
            // {
            //     tilemap.rows = value.as_int32();
            //     read_rows = true;
            // }
            break;
        }
    });

    if (not read_tileset)
        return cmm::err(pmb::fmt::tilemap_error::missing_tileset);

    if (not read_columns)
        return cmm::err(pmb::fmt::tilemap_error::missing_columns);

    if (not read_rows)
        return cmm::err(pmb::fmt::tilemap_error::missing_rows);

    if (not read_map)
        return cmm::err(pmb::fmt::tilemap_error::missing_map);

    return cmm::ok(tilemap);
}


auto pmb::fmt::write_tilemap(const pmb::fmt::tilemap_data& ts,
                        cmm::rspan               output_buffer) noexcept
    -> cmm::rspan
{
    auto writer = cmm::jb_writer{output_buffer};

    if (not writer.write(int(pmb::fmt::tilemap_attribute_id::image),
                         ts.image))
        return {};

    if (not writer.write(int(pmb::fmt::tilemap_attribute_id::columns),
                         ts.columns))
        return {};

    if (not writer.write(int(pmb::fmt::tilemap_attribute_id::tile_width),
                         ts.tile_width))
        return {};

    if (not writer.write(int(pmb::fmt::tilemap_attribute_id::tile_height),
                         ts.tile_height))
        return {};

    if (not writer.write(int(pmb::fmt::tilemap_attribute_id::spacing),
                         ts.spacing))
        return {};

    return writer.span();
}
