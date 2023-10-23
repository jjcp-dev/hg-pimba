#include "pmb/shader_store.hpp"


static auto compile_mt_sprite_shader()
    -> lgf::shader
{
    lgf::opengl_shader_src src;

    src.vertex_shader = R"(
        #version 120

        #define in_Position     in_Slot0
        #define in_UV0          in_Slot1
        #define in_SamplerIndex in_Slot2

        attribute vec4  in_Position;
        attribute vec2  in_UV0;
        attribute float in_SamplerIndex;

        uniform mat4 u_MVP;

        varying vec2 v_UV0;

        void main()
        {
            v_UV0 = in_UV0;

            gl_Position = u_MVP * in_Position;
        }
    )";

    src.fragment_shader = R"(
        #version 120

        uniform sampler2D u_Sampler[1];

        varying vec2 v_UV0;

        void main() {
            vec4 color = vec4(1.0);
            color = texture2D(u_Sampler[0], v_UV0);
            gl_FragColor = color;
            // gl_FragColor = vec4(v_UV0.x, v_UV0.y, 0.0, 1.0);
            // gl_FragColor = vec4(v_UV0.x, 0.0, 0.0, 1.0);
            // gl_FragColor = vec4(0.0, v_UV0.y, 0.0, 1.0);
        }
    )";

    return lgf::shader{src};
}


void pmb::shader_store::compile(pmb::shader_options opts)
{
    switch (opts) {
    case pmb::shader_options::multi_textured_sprite:
        m_mt_sprite = compile_mt_sprite_shader();
        break;
    default:
        break;
    }
}
