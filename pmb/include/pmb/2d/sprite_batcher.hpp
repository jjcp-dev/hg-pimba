#ifndef PMB_2D_SPRITE_BATCHER_HPP_9DMHRVEK
#define PMB_2D_SPRITE_BATCHER_HPP_9DMHRVEK

#include <cassert>

#include "glm/glm.hpp"

#include "cmm/mem/align.hpp"
#include "cmm/span.hpp"

#include "lgf/vtx_buffer.hpp"
#include "lgf/vtx_range.hpp"

#include "./sprite.hpp"


namespace pmb {

class sprite_batcher_writer {
public:
    struct vertex {
        float         x, y;
        std::uint16_t u, v;
        float         sampler;
    };

    struct quad {
        // FIXME: this structure is too big for encoding one sprite
        vertex v0;
        vertex v1;
        vertex v2;

        vertex v3;
        vertex v4;
        vertex v5;
    };

    sprite_batcher_writer() = default;

    sprite_batcher_writer(const sprite_batcher_writer&) = delete;

    sprite_batcher_writer(sprite_batcher_writer&& x)
        : m_buffer{x.m_buffer}, m_top{x.m_top}
    {
        x = {};
    }

    explicit sprite_batcher_writer(cmm::span<quad> buffer)
        : m_buffer{buffer}
    { }

    auto operator=(const sprite_batcher_writer&)
        -> sprite_batcher_writer& = delete;

    auto operator=(sprite_batcher_writer&& rhs) noexcept
        -> sprite_batcher_writer&
    {
        if (this != &rhs)
        {
            m_buffer = rhs.m_buffer;
            m_top = rhs.m_top;

            rhs.m_buffer = {};
            rhs.m_top = 0;
        }

        return *this;
    }

    bool add(glm::vec2 pos, short sprite_width, short sprite_height,
             pmb::rect<unsigned short> uvs, int sampler_index) noexcept;

    bool add(const pmb::sprite& sprite, glm::vec2 pos, int index=0) noexcept
    {
        return add(pos, sprite.width(), sprite.height(), sprite.uvs(), index);
    }

    auto span() noexcept
        -> cmm::span<quad>
    {
        return {m_buffer.data(), m_top};
    }

    auto span() const noexcept
        -> cmm::span<const quad>
    {
        return {m_buffer.data(), m_top};
    }

private:

    cmm::span<quad> m_buffer;
    int             m_top = 0;
};


class sprite_batcher {
public:

    sprite_batcher() = default;

    sprite_batcher(const sprite_batcher&) = delete;

    sprite_batcher(sprite_batcher&&) = default;

    explicit sprite_batcher(int sprite_count) noexcept;

    explicit sprite_batcher(lgf::vtx_buffer&& buffer) noexcept
    {
        assert((buffer.decl() == lgf::vtx_decl{
            {2, false, lgf::vtx_decl::type::f32},
            {2, true,  lgf::vtx_decl::type::u16},
            {1, false, lgf::vtx_decl::type::f32},
        }));

        m_vtx_buffer = std::move(buffer);
    }

    auto operator=(const sprite_batcher&)
        -> sprite_batcher& = delete;

    auto operator=(sprite_batcher&&)
        -> sprite_batcher& = default;

    void begin() noexcept
    {
        auto span = m_vtx_buffer.map(lgf::buffer_access::write);

        using quad = pmb::sprite_batcher_writer::quad;
        if (cmm::align_of(span.data()) >= alignof(quad))
        {
            m_writer = pmb::sprite_batcher_writer{{
                reinterpret_cast<quad*>(span.data()),
                static_cast<int>(span.size_bytes() / sizeof(quad))
            }};
        }
        else
        {
            m_writer = {};
        }
    }

    bool add(glm::vec2 pos, short sprite_width, short sprite_height,
             pmb::rect<unsigned short> uvs,
             int sampler_index) noexcept
    {
        return m_writer.add(pos, sprite_width, sprite_height,
                            uvs, sampler_index);
    }

    bool add(const pmb::sprite& sprite, glm::vec2 pos, int index=0) noexcept
    {
        return m_writer.add(sprite, pos, index);
    }

    bool end() noexcept
    {
        return m_vtx_buffer.unmap();
    }

    auto vtx_buffer() const noexcept
        -> lgf::vtx_buffer_handle
    {
        return m_vtx_buffer;
    }

    auto vtx_range() const noexcept
        -> lgf::vtx_range
    {
        auto count = m_writer.span().size_bytes()
                   / sizeof(pmb::sprite_batcher_writer::vertex);

        return {0, static_cast<int>(count)};
    }

private:

    lgf::vtx_buffer            m_vtx_buffer;
    pmb::sprite_batcher_writer m_writer;
};

} /* pmb */

#endif
