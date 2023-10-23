#include "pmb/formats/tileset.hpp"

#include "cmm/jb/parser.hpp"
#include "cmm/jb/writer.hpp"


auto pmb::fmt::parse_tileset(cmm::cspan buffer) noexcept
    -> cmm::result<pmb::fmt::tileset_data,
                   pmb::fmt::tileset_error>
{
    auto parser = cmm::jb{buffer};

    pmb::fmt::tileset_data tileset;

    bool read_image = false;
    bool read_columns = false;
    bool read_tile_width = false;
    bool read_tile_height = false;
    bool read_spacing = false;

    parser.for_each([&] (const cmm::jb::value& value) {
        switch (value.id()) {
        case int(pmb::fmt::tileset_attribute_id::image):
            if (value.type() == cmm::jb::type::str)
            {
                tileset.image = value.as_string();
                read_image = true;
            }
            break;

            case int(pmb::fmt::tileset_attribute_id::columns):
            if (value.type() == cmm::jb::type::i32)
            {
                tileset.columns = value.as_int32();
                read_columns = true;
            }
            break;

            case int(pmb::fmt::tileset_attribute_id::tile_width):
            if (value.type() == cmm::jb::type::i32)
            {
                tileset.tile_width = value.as_int32();
                read_tile_width = true;
            }
            break;

            case int(pmb::fmt::tileset_attribute_id::tile_height):
            if (value.type() == cmm::jb::type::i32)
            {
                tileset.tile_height = value.as_int32();
                read_tile_height = true;
            }
            break;

            case int(pmb::fmt::tileset_attribute_id::spacing):
            if (value.type() == cmm::jb::type::i32)
            {
                tileset.spacing = value.as_int32();
                read_spacing = true;
            }
            break;
        }
    });

    if (not read_image)
        return cmm::err(pmb::fmt::tileset_error::missing_image);

    if (not read_columns)
        return cmm::err(pmb::fmt::tileset_error::missing_columns);

    if (not read_tile_width)
        return cmm::err(pmb::fmt::tileset_error::missing_tile_width);

    if (not read_tile_height)
        return cmm::err(pmb::fmt::tileset_error::missing_tile_height);

    if (not read_spacing)
        return cmm::err(pmb::fmt::tileset_error::missing_spacing);

    return cmm::ok(tileset);
}


auto pmb::fmt::write_tileset(const pmb::fmt::tileset_data& ts,
                        cmm::rspan               output_buffer) noexcept
    -> cmm::rspan
{
    auto writer = cmm::jb_writer{output_buffer};

    if (not writer.write(int(pmb::fmt::tileset_attribute_id::image),
                         ts.image))
        return {};

    if (not writer.write(int(pmb::fmt::tileset_attribute_id::columns),
                         ts.columns))
        return {};

    if (not writer.write(int(pmb::fmt::tileset_attribute_id::tile_width),
                         ts.tile_width))
        return {};

    if (not writer.write(int(pmb::fmt::tileset_attribute_id::tile_height),
                         ts.tile_height))
        return {};

    if (not writer.write(int(pmb::fmt::tileset_attribute_id::spacing),
                         ts.spacing))
        return {};

    return writer.span();
}


// template<typename T>
// auto write(cmm::jb_writer&           writer,
//            std::ostream&             output_stream,
//            cmm::rspan                temporary_buffer,
//            pmb::fmt::tileset_attribute_id id,
//            T                         value)
//     -> bool
// {
//     if (not writer.write(int(id), value))
//     {
//         output_stream.write((const char*) writer.span().data(),
//                             writer.span().size_bytes());

//         writer = cmm::jb_writer(temporary_buffer);

//         if (not writer.write(int(id), value))
//             return false;
//     }

//     return true;
// }


// auto pmb::fmt::write_tileset(const pmb::fmt::tileset_data& ts,
//                    std::ostream&            output_stream,
//                    cmm::rspan               temporary_buffer)
//     -> bool
// {
//     auto writer = cmm::jb_writer{temporary_buffer};

//     if (not write(writer, output_stream, temporary_buffer,
//                   pmb::fmt::tileset_attribute_id::image, ts.image))
//         return false;

//     if (not write(writer, output_stream, temporary_buffer,
//                   pmb::fmt::tileset_attribute_id::columns, ts.columns))
//         return false;

//     if (not write(writer, output_stream, temporary_buffer,
//                   pmb::fmt::tileset_attribute_id::tile_width, ts.tile_width))
//         return false;

//     if (not write(writer, output_stream, temporary_buffer,
//                   pmb::fmt::tileset_attribute_id::tile_height, ts.tile_height))
//         return false;

//     if (not write(writer, output_stream, temporary_buffer,
//                   pmb::fmt::tileset_attribute_id::spacing, ts.spacing))
//         return false;

//     if (writer.span().size())
//         output_stream.write((const char*) writer.span().data(),
//                             writer.span().size_bytes());

//     return true;
// }
