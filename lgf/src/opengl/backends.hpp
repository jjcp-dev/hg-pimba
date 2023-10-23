#ifndef LGF_BACKENDS_HPP_ICHR82M7
#define LGF_BACKENDS_HPP_ICHR82M7

#include "vtx_buffer_backend.hpp"
#include "texture_backend.hpp"
#include "shader_backend.hpp"


namespace lgf {

class backends {
public:
    static lgf::vtx_buffer_backend vtx_buffer;
    static lgf::texture_backend    texture;
    static lgf::shader_backend     shader;
};

} /* lgf */

#endif
