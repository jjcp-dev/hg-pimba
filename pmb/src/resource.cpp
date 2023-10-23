#include "gsl/gsl"
#include "stb_image.h"

#include "cmm/jb/parser.hpp"

#include "pmb/resource.hpp"

#include "pmb/formats/tileset.hpp"


auto pmb::resource::load_texture(const char* path) noexcept
    -> lgf::texture
{
    auto asset = file_system->read(path);

    int x, y;
    auto image_data = stbi_load_from_memory(asset.cspan().data(),
                                            asset.cspan().size(),
                                            &x,
                                            &y,
                                            nullptr,
                                            4);
    auto free_image = gsl::finally([&]() {
        stbi_image_free(image_data);
    });

    lgf::image img;
    img.width = x;
    img.height = y;
    img.channels = 4;
    img.image_data = {image_data, x * y * 4};

    return {img, {}};
}


auto pmb::resource::load_tileset(const char* path) noexcept
    -> pmb::tileset
{
    auto asset = file_system->read(path);

    auto result = pmb::fmt::parse_tileset(asset.cspan());

    if (result.is_valid())
    {
        auto ts = result.value();

        auto texture = load_texture(ts.image);

        return {
            std::move(texture),
            (short) ts.tile_width,
            (short) ts.tile_height,
            (short) ts.columns,
            0,
            (short) ts.spacing
        };
    }

    return {};
}
