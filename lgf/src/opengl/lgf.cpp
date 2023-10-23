#include <algorithm>

#include "glm/gtc/type_ptr.hpp"

#include "lgf/lgf.hpp"

#include "opengl.hpp"
#include "commands_backend.hpp"

#include "../log.hpp"


bool lgf::init(const lgf::config& config)
{
    lgf::log = config.log_fn;
    lgf::log_err = config.log_err_fn;

    return lgf::opengl::init();
}


void lgf::shutdown()
{
    lgf::opengl::shutdown();
}


static void run(const lgf::opengl_clear_command* cmd)
{
    glClearColor(cmd->r, cmd->g, cmd->b, 1.0f);
    glClear(cmd->flags);
}


static void run(const lgf::viewport* cmd)
{
    glViewport(cmd->x, cmd->y, cmd->w, cmd->h);
}


static void run(const lgf::opengl_draw_command* cmd)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(cmd->shader.program_id);

    for (int i = 0; i < cmd->shader.sampler_length; i++)
    {
        if (cmd->texture[i])
        {
            glUniform1i(cmd->shader.sampler + i, i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, cmd->texture[i]);
        }
    }

    if (cmd->shader.mvp >= 0)
    {
        glUniformMatrix4fv(cmd->shader.mvp, 1, false,
                           glm::value_ptr(cmd->mvp));
    }

    if (cmd->vao_id)
    {
        glBindVertexArray(cmd->vao_id);
    }
    else
    {
        LGF_FIXME();
    }

    glDrawArrays(GL_TRIANGLES, cmd->vtx_range.start(), cmd->vtx_range.count());

    glBindVertexArray(0);
}


void lgf::submit(lgf::command_list& list)
{
    std::sort(list.begin(),
              list.end(),
              [] (const auto& a, const auto& b) {
                return a.key < b.key;
              });

    for (auto& node : list)
    {
        switch (node.type) {
        case lgf::command_type::clear:
            run((lgf::opengl_clear_command*) node.command);
            break;

        case lgf::command_type::viewport:
            run((lgf::viewport*) node.command);
            break;

        case lgf::command_type::draw:
            run((lgf::opengl_draw_command*) node.command);
            break;
        }
    }

    list.reset();
}
