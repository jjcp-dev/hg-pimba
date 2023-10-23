#ifndef LGF_TEXTURE_BACKEND_HPP_X1CIOZNT
#define LGF_TEXTURE_BACKEND_HPP_X1CIOZNT

#include "opengl.hpp"

#include "cmm/multi_pool.hpp"

#include "lgf/texture.hpp"


namespace lgf {

struct texture_data {
    GLuint texture_id;
    int    width = 0;
    int    height = 0;
};


class texture_backend {
public:

    cmm::multi_pool<lgf::texture_data, 12> pool;

    auto get(lgf::texture_handle h) const noexcept
        -> lgf::texture_data*
    {
        return reinterpret_cast<lgf::texture_data*>(h._id());
    }
};

} /* lgf */

#endif
