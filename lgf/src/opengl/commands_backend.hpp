#ifndef LGF_COMMANDS_BACKEND_HPP_B2GIDBFA
#define LGF_COMMANDS_BACKEND_HPP_B2GIDBFA

#include "glm/glm.hpp"

#include "lgf/vtx_range.hpp"
#include "lgf/commands.hpp"

#include "opengl.hpp"

#include "./shader_backend.hpp"


namespace lgf {

struct opengl_clear_command {
    GLenum flags;
    float  r;
    float  g;
    float  b;
};


struct opengl_draw_command {
    // vertices
    lgf::vtx_decl*        decl           = nullptr;
    GLuint                vao_id         = 0;
    GLuint                vbo_id         = 0;
    lgf::vtx_range        vtx_range;

    // material
    lgf::shader_data      shader;
    std::array<GLuint, 2> texture        = {0, 0};

    // uniforms
    glm::mat4             mvp            = glm::mat4{1.0f};
};

} /* lgf */

#endif
