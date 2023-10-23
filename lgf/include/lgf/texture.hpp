#ifndef LGF_TEXTURE_HPP_WMZT9RBC
#define LGF_TEXTURE_HPP_WMZT9RBC

#include "internal/handle_owner.hpp"
#include "./image.hpp"


namespace lgf {

enum class wrap_mode {
    repeat,
    mirrored_repeat,
    clamp_to_edge,
    clamp_to_border
};


enum class filter_mode {
    nearest,
    linear
};


struct texture_config {
    lgf::wrap_mode wrap_s = lgf::wrap_mode::repeat;
    lgf::wrap_mode wrap_t = lgf::wrap_mode::repeat;

    lgf::filter_mode min_filter = lgf::filter_mode::linear;
    lgf::filter_mode mag_filter = lgf::filter_mode::linear;
};


class texture_handle {
public:
    using id_type = void*;

    auto width() const noexcept
        -> int;

    auto height() const noexcept
        -> int;

    auto _id() noexcept
        -> id_type
    {
        return m_id;
    }

protected:
    id_type m_id = {};

    void destroy();
};


class texture : public lgf::texture_handle {
public:
    LGF_HANDLE_OWNER(texture);

    texture() = default;

    texture(lgf::image, lgf::texture_config={});

   ~texture()
    {
        destroy();
    }
};

} /* lgf */

#endif
