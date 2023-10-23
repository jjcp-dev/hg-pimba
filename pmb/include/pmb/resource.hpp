#ifndef PMB_RESOURCE_HPP_BXD8JYON
#define PMB_RESOURCE_HPP_BXD8JYON

#include "2d/sprite.hpp"

#include "lgf/texture.hpp"

#include "fs/file_system.hpp"

#include "./tileset.hpp"


namespace pmb {

class resource {
public:
    pmb::file_system* file_system;

    resource(pmb::file_system* fs)
        : file_system{fs}
    {}

    auto load_texture(const char* path) noexcept
        -> lgf::texture;

    auto load_tileset(const char* path) noexcept
        -> pmb::tileset;

    // auto load_animation(const char* path) noexcept
    //     -> pmb::anim::movie;

    // auto load_tileset(const char* path) noexcept
    //     -> pmb::tileset;
};

} /* pmb */

#endif
