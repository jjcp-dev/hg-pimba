#include "shader_backend.hpp"

#include "backends.hpp"
#include "to_gl.hpp"

#include "../log.hpp"



static GLuint compile_shaders(const char** vertex_shader, int vcount,
                              const char** fragment_shader, int fcount)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, vcount, vertex_shader, nullptr);
    glCompileShader(vertex_shader_id);

    GLint is_compiled = 0;
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &is_compiled);
    if(is_compiled == GL_FALSE)
    {
        GLint max_length = 0;
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(vertex_shader_id, max_length,
                           &max_length, &info_log[0]);

        glDeleteShader(vertex_shader_id);

        // lgf::log_err("%s\n", info_log.data());

        return 0;
    }

    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, fcount, fragment_shader, nullptr);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
        GLint max_length = 0;
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(fragment_shader_id, max_length,
                           &max_length, &info_log[0]);

        glDeleteShader(fragment_shader_id);
        glDeleteShader(vertex_shader_id);

        // lgf::log_err("%s\n", info_log.data());

        return 0;
    }

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    glBindAttribLocation(program_id, 0, "in_Slot0");
    glBindAttribLocation(program_id, 1, "in_Slot1");
    glBindAttribLocation(program_id, 2, "in_Slot2");
    glBindAttribLocation(program_id, 3, "in_Slot3");
    glBindAttribLocation(program_id, 4, "in_Slot4");
    glBindAttribLocation(program_id, 5, "in_Slot5");
    glBindAttribLocation(program_id, 6, "in_Slot6");
    glBindAttribLocation(program_id, 7, "in_Slot7");

    glLinkProgram(program_id);

    GLint is_linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE)
    {
        GLint max_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(program_id, max_length,
                            &max_length, &info_log[0]);

        glDeleteProgram(program_id);
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);

        // lgf::log_err("%s\n", info_log.data());

        return 0;
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    return program_id;
}


lgf::shader::shader(lgf::opengl_shader_src src)
{
    auto data = lgf::backends::shader.pool.allocate();

    if (not data)
    {
        LGF_FIXME();
        return;
    }

    m_id = data;

    data->program_id = compile_shaders(&src.vertex_shader, 1,
                                       &src.fragment_shader, 1);

    data->mvp = glGetUniformLocation(data->program_id, "u_MVP");
    data->sampler = glGetUniformLocation(data->program_id, "u_Sampler");

    if (data->sampler >= 0)
    {
        GLenum type;
        GLint size;
        char c;
        glGetActiveUniform(data->program_id,
                           data->sampler,
                           1,
                           nullptr,
                           &size,
                           &type,
                           &c);

        data->sampler_length = size;
    }
}


void lgf::shader_handle::destroy()
{
    auto data = lgf::backends::shader.get(*this);

    if (data)
    {
        glDeleteProgram(data->program_id);
        m_id = {};
    }
}
