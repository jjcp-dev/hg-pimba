#include "lgf/command_list.hpp"

#include "backends.hpp"
#include "commands_backend.hpp"
#include "to_gl.hpp"


template<typename T, typename... Args>
auto lgf::command_list::allocate(lgf::sort_key key,
                                 lgf::command_type type,
                                 Args&&... args)
    -> T*
{
    auto left  = cmm::align_forward(m_left, alignof(T));
    auto right = m_right - sizeof(header);

    if (left + sizeof(T) <= right)
    {
        auto c = new (left) T{std::forward<Args>(args)...};
        auto r = new (right) header{};

        r->command = c;
        r->key     = key;
        r->type    = type;

        m_left  = left + sizeof(T);
        m_right = right;

        return c;
    }

    return nullptr;
}


auto lgf::command_list::add(lgf::sort_key key, const lgf::clear_command& cmd)
    -> bool
{
    static_assert(
        std::is_trivially_destructible<lgf::opengl_clear_command>::value,
        "`lgf::opengl_clear_command` must be `trivially_destructible`");

    auto c = allocate<lgf::opengl_clear_command>(
        key, lgf::command_type::clear);

    if (not c)
        return false;

    c->flags = lgf::to_gl(cmd.mode);
    c->r     = cmd.color.r;
    c->g     = cmd.color.g;
    c->b     = cmd.color.b;

    return true;
}


auto lgf::command_list::add(lgf::sort_key key, const lgf::viewport& cmd)
    -> bool
{
    static_assert(
        std::is_trivially_destructible<lgf::viewport>::value,
        "`lgf::viewport` must be `trivially_destructible`");

    auto c = allocate<lgf::viewport>(key, lgf::command_type::viewport, cmd);

    return c != nullptr;
}


auto lgf::command_list::add(lgf::sort_key key, const lgf::draw_command& cmd)
    -> bool
{
    static_assert(
        std::is_trivially_destructible<lgf::opengl_draw_command>::value,
        "`lgf::opengl_draw_command` must be `trivially_destructible`");

    auto c = allocate<lgf::opengl_draw_command>(key, lgf::command_type::draw);

    if (not c)
        return false;

    // vertices
    // ----------------------------------

    auto vtx_buffer_data = lgf::backends::vtx_buffer.get(cmd.vtx);

    if (vtx_buffer_data)
    {
        c->decl       = &vtx_buffer_data->decl;
        c->vao_id     = vtx_buffer_data->vao_id;
        c->vbo_id     = vtx_buffer_data->vbo_id;
        c->vtx_range  = cmd.vtx_range;
    }

    // material
    // ----------------------------------

    auto shader_data = lgf::backends::shader.get(cmd.shader);

    if (shader_data)
    {
        c->shader = *shader_data;

        for (int i = 0; i < static_cast<int>(cmd.textures.size()); i++)
        {
            auto texture_data =
                lgf::backends::texture.get(cmd.textures[i]);

            if (texture_data)
            {
                c->texture[i] = texture_data->texture_id;
            }
        }
    }

    // uniforms
    // ----------------------------------

    c->mvp = cmd.mvp;

    return true;
}
