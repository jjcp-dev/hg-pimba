#ifndef SHADER_BACKEND_HPP_BDIZK4E2
#define SHADER_BACKEND_HPP_BDIZK4E2

#include "opengl.hpp"

#include "cmm/multi_pool.hpp"

#include "lgf/shader.hpp"


namespace lgf {

struct shader_data {
    GLuint program_id     = 0;
    GLint  mvp            = -1;
    GLint  sampler        = -1;
    int    sampler_length = 0;
};


class shader_backend {
public:

    cmm::multi_pool<lgf::shader_data, 12> pool;

    auto get(lgf::shader_handle h) const noexcept
        -> lgf::shader_data*
    {
        return reinterpret_cast<lgf::shader_data*>(h._id());
    }
};

} /* lgf */

#endif
