#include "lgf/texture.hpp"

#include "backends.hpp"
#include "to_gl.hpp"

#include "../log.hpp"


lgf::texture::texture(lgf::image img, lgf::texture_config cfg)
{
    auto data = lgf::backends::texture.pool.allocate();

    if (not data)
    {
        LGF_FIXME();
    }

    glGenTextures(1, &data->texture_id);
    glBindTexture(GL_TEXTURE_2D, data->texture_id);

    GLenum wrap_s = lgf::to_gl(cfg.wrap_s);
    GLenum wrap_t = lgf::to_gl(cfg.wrap_t);

    GLenum min_filter = lgf::to_gl(cfg.min_filter);
    GLenum mag_filter = lgf::to_gl(cfg.mag_filter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        img.width,
        img.height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        img.image_data.data());

    data->width = img.width;
    data->height = img.height;

    glBindTexture(GL_TEXTURE_2D, 0);

    m_id = data;
}


void lgf::texture_handle::destroy()
{
    auto data = reinterpret_cast<lgf::texture_data*>(m_id);

    if (data)
    {
        glDeleteTextures(1, &data->texture_id);

        lgf::backends::texture.pool.free(data);
        m_id = nullptr;
    }
}


auto lgf::texture_handle::width() const noexcept
    -> int
{
    auto data = reinterpret_cast<lgf::texture_data*>(m_id);

    if (not data)
        return 0;

    return data->width;
}


auto lgf::texture_handle::height() const noexcept
    -> int
{
    auto data = reinterpret_cast<lgf::texture_data*>(m_id);

    if (not data)
        return 0;

    return data->height;
}
