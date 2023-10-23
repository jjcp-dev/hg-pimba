#ifndef LGF_COMMANDS_HPP_LIBJZPSB
#define LGF_COMMANDS_HPP_LIBJZPSB

#include <array>

#include "glm/glm.hpp"

#include "vtx_buffer.hpp"
#include "vtx_range.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "viewport.hpp"
#include "clear_mode.hpp"


namespace lgf {

enum class command_type {
    clear,
    viewport,
    draw,
};


struct clear_command {
    lgf::clear_mode mode;
    glm::vec3       color;
};


struct draw_command {
    lgf::vtx_buffer_handle             vtx;
    lgf::vtx_range                     vtx_range;
    lgf::shader_handle                 shader;
    std::array<lgf::texture_handle, 2> textures;

    glm::mat4                          mvp{1.0f};
};

} /* lgf */

#endif
