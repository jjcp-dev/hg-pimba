#include "lgf/vtx_buffer.hpp"

#include "backends.hpp"
#include "to_gl.hpp"

#include "../log.hpp"


static lgf::vtx_buffer_data _invalid;


static void construct_vtx_buffer(lgf::vtx_buffer_data* data,
                                 lgf::vtx_usage        usage,
                                 const lgf::vtx_decl&  decl,
                                 const void*           buffer,
                                 int                   size)
{
    // data->buffer = nullptr;
    data->size   = size;
    data->vbo_id = 0;
    data->vao_id = 0;
    data->usage  = usage;
    data->decl   = decl;

    glGenBuffers(1, &data->vbo_id);

    glBindBuffer(GL_ARRAY_BUFFER, data->vbo_id);
    glBufferData(GL_ARRAY_BUFFER, size, buffer, lgf::to_gl(usage));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (not lgf::opengl::features.map_buffer)
    {
        LGF_FIXME();
    }

    switch (usage) {
    case lgf::vtx_usage::static_draw:
        break;

    case lgf::vtx_usage::stream_draw:
        break;
    }

    if (lgf::opengl::features.vertex_array_object)
    {
        glGenVertexArrays(1, &data->vao_id);

        glBindVertexArray(data->vao_id);
        glBindBuffer(GL_ARRAY_BUFFER, data->vbo_id);

        char* offset = 0;
        char* next_offset = 0;
        for (int i = 0; i < std::distance(decl.begin(), decl.end()); i++)
        {
            const auto& d = decl.begin()[i];

            GLenum type = 0;
            switch (d.type()) {
            case lgf::vtx_decl::type::u8:
                next_offset += d.count() * 1;
                type = GL_UNSIGNED_BYTE;
                break;
            case lgf::vtx_decl::type::i8:
                next_offset += d.count() * 1;
                type = GL_BYTE;
                break;
            case lgf::vtx_decl::type::u16:
                next_offset += d.count() * 2;
                type = GL_UNSIGNED_SHORT;
                break;
            case lgf::vtx_decl::type::i16:
                next_offset += d.count() * 2;
                type = GL_SHORT;
                break;
            case lgf::vtx_decl::type::u32:
                next_offset += d.count() * 4;
                type = GL_UNSIGNED_INT;
                break;
            case lgf::vtx_decl::type::i32:
                next_offset += d.count() * 4;
                type = GL_INT;
                break;
            case lgf::vtx_decl::type::f32:
                next_offset += d.count() * 4;
                type = GL_FLOAT;
                break;
            case lgf::vtx_decl::type::none:
                continue;
            }

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                i, d.count(), type, d.normalized(), decl.stride(), offset);

            offset = next_offset;
        }

        glBindVertexArray(0);
    }
}


lgf::vtx_buffer::vtx_buffer(lgf::vtx_usage usage,
                            lgf::vtx_decl  decl,
                            int            count) noexcept
{
    auto data = lgf::backends::vtx_buffer.pool.allocate();

    if (not data)
    {
        LGF_FIXME();
        return;
    }

    m_id = data;

    const auto size = decl.stride() * count;

    construct_vtx_buffer(data, usage, decl, nullptr, size);
}


lgf::vtx_buffer::vtx_buffer(lgf::vtx_usage usage,
                            lgf::vtx_decl  decl,
                            cmm::cspan     buffer_data) noexcept
{
    auto data = lgf::backends::vtx_buffer.pool.allocate();

    if (not data)
    {
        LGF_FIXME();
        return;
    }

    m_id = data;

    auto size = buffer_data.size_bytes();
    auto ptr = buffer_data.data();

    construct_vtx_buffer(data, usage, decl, ptr, size);
}


lgf::vtx_buffer::~vtx_buffer() noexcept
{
    destroy();
}


void lgf::vtx_buffer_handle::destroy() noexcept
{
    auto data = reinterpret_cast<lgf::vtx_buffer_data*>(m_id);

    if (data)
    {
        if (data->vao_id)
            glDeleteVertexArrays(1, &data->vao_id);

        if (data->vbo_id)
            glDeleteBuffers(1, &data->vbo_id);

        lgf::backends::vtx_buffer.pool.free(data);
        m_id = nullptr;
    }
}


auto lgf::vtx_buffer_handle::usage() const noexcept
    -> lgf::vtx_usage
{
    auto data = reinterpret_cast<const lgf::vtx_buffer_data*>(m_id);
    if (not data)
    {
        LGF_FIXME();
        return _invalid.usage;
    }

    return data->usage;
}


auto lgf::vtx_buffer_handle::decl() const noexcept
    -> const lgf::vtx_decl&
{
    auto data = reinterpret_cast<const lgf::vtx_buffer_data*>(m_id);
    if (not data)
    {
        LGF_FIXME();
        return _invalid.decl;
    }

    return data->decl;
}


auto lgf::vtx_buffer_handle::map(lgf::buffer_access access) noexcept
    -> cmm::rspan
{
    auto data = reinterpret_cast<const lgf::vtx_buffer_data*>(m_id);
    if (not data)
    {
        LGF_FIXME();
        return {};
    }

    if (lgf::opengl::features.map_buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, data->vbo_id);

        GLenum flags = 0;
        if (cmm::any(access & (lgf::buffer_access::read |
                               lgf::buffer_access::write)))
        {
            flags = GL_READ_WRITE;
        }
        else if (cmm::any(access & lgf::buffer_access::read))
        {
            flags = GL_READ_ONLY;
        }
        else if (cmm::any(access & lgf::buffer_access::write))
        {
            flags = GL_WRITE_ONLY;
        }
        else
        {
            LGF_FIXME();
        }

        auto ptr = glMapBuffer(GL_ARRAY_BUFFER, flags);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        if (ptr == nullptr)
            return {};

        return {ptr, data->size};
    }
    else
    {
        LGF_FIXME();
    }

    return {};
}


auto lgf::vtx_buffer_handle::unmap() noexcept
    -> bool
{
    auto data = reinterpret_cast<const lgf::vtx_buffer_data*>(m_id);
    if (not data)
    {
        LGF_FIXME();
        return true;
    }

    if (lgf::opengl::features.map_buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, data->vbo_id);
        auto result = glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return result;
    }
    else
    {
        LGF_FIXME();
        return false;
    }
}
