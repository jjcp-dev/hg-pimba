#ifndef LGF_VTX_BUFFER_BACKEND_HPP_WIU8BXJA
#define LGF_VTX_BUFFER_BACKEND_HPP_WIU8BXJA

#include "opengl.hpp"

#include "cmm/multi_pool.hpp"

#include "lgf/vtx_buffer.hpp"



namespace lgf {

struct vtx_buffer_data {
    // char*          buffer;
    int            size;
    GLuint         vbo_id;
    GLuint         vao_id;
    lgf::vtx_usage usage;
    lgf::vtx_decl  decl;
};


class vtx_buffer_backend {
public:

    cmm::multi_pool<lgf::vtx_buffer_data, 12> pool;

    auto get(lgf::vtx_buffer_handle h) const noexcept
        -> lgf::vtx_buffer_data*
    {
        return reinterpret_cast<lgf::vtx_buffer_data*>(h._id());
    }
};

} /* lgf */

#endif
