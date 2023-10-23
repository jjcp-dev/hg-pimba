#include <cassert>
#include <cstdio>

#include "pmb/2d/sprite_batcher.hpp"

#include "cmm/mem/align.hpp"


pmb::sprite_batcher::sprite_batcher(int sprite_count) noexcept
{
    m_vtx_buffer = lgf::vtx_buffer{
        lgf::vtx_usage::stream_draw,
        lgf::vtx_decl{
            {2, false, lgf::vtx_decl::type::f32},
            {2, true,  lgf::vtx_decl::type::u16},
            {1, false, lgf::vtx_decl::type::f32},
        },
        sprite_count * (int) sizeof(pmb::sprite_batcher_writer::quad)
    };
}


bool pmb::sprite_batcher_writer::add(glm::vec2 pos,
                                     short sprite_width,
                                     short sprite_height,
                                     pmb::rect<unsigned short> uvs,
                                     int sampler_index) noexcept
{
    if (m_top >= m_buffer.size())
        return false;

    auto& q = m_buffer[m_top++];

    // top-left
    q.v0.x = pos.x;
    q.v0.y = pos.y;
    q.v0.u = uvs.x0;
    q.v0.v = uvs.y0;
    q.v0.sampler = sampler_index;

    // bottom-left
    q.v1.x = pos.x;
    q.v1.y = pos.y + sprite_height;
    q.v1.u = uvs.x0;
    q.v1.v = uvs.y1;
    q.v1.sampler = sampler_index;

    // bottom-right
    q.v2.x = pos.x + sprite_width;
    q.v2.y = pos.y + sprite_height;
    q.v2.u = uvs.x1;
    q.v2.v = uvs.y1;
    q.v2.sampler = sampler_index;

    // top-left
    q.v3.x = pos.x;
    q.v3.y = pos.y;
    q.v3.u = uvs.x0;
    q.v3.v = uvs.y0;
    q.v3.sampler = sampler_index;

    // bottom-right
    q.v4.x = pos.x + sprite_width;
    q.v4.y = pos.y + sprite_height;
    q.v4.u = uvs.x1;
    q.v4.v = uvs.y1;
    q.v4.sampler = sampler_index;

    // top-right
    q.v5.x = pos.x + sprite_width;
    q.v5.y = pos.y;
    q.v5.u = uvs.x1;
    q.v5.v = uvs.y0;
    q.v5.sampler = sampler_index;

    // printf("%f, %f, %i, %i, %f\n", q.v0.x, q.v0.y, q.v0.u, q.v0.v, q.v0.sampler);
    // printf("%f, %f, %i, %i, %f\n", q.v1.x, q.v1.y, q.v1.u, q.v1.v, q.v1.sampler);
    // printf("%f, %f, %i, %i, %f\n", q.v2.x, q.v2.y, q.v2.u, q.v2.v, q.v2.sampler);
    // printf("%f, %f, %i, %i, %f\n", q.v3.x, q.v3.y, q.v3.u, q.v3.v, q.v3.sampler);
    // printf("%f, %f, %i, %i, %f\n", q.v4.x, q.v4.y, q.v4.u, q.v4.v, q.v4.sampler);
    // printf("%f, %f, %i, %i, %f\n", q.v5.x, q.v5.y, q.v5.u, q.v5.v, q.v5.sampler);
    // printf("-----------------------\n");

    return true;
}
