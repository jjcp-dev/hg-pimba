#ifndef LGF_TO_GL_HPP_NQFS0IPG
#define LGF_TO_GL_HPP_NQFS0IPG

#include "opengl.hpp"

#include "lgf/clear_mode.hpp"
#include "lgf/vtx_usage.hpp"
#include "lgf/vtx_decl.hpp"
#include "lgf/texture.hpp"


namespace lgf {

inline auto to_gl(lgf::clear_mode x)
    -> GLenum
{
    GLenum result = 0;

    if (cmm::any(x & lgf::clear_mode::color))
        result |= GL_COLOR_BUFFER_BIT;

    if (cmm::any(x & lgf::clear_mode::depth))
        result |= GL_DEPTH_BUFFER_BIT;

    return result;
}


inline auto to_gl(lgf::vtx_usage x)
    -> GLenum
{
    switch (x) {
    case lgf::vtx_usage::static_draw:
        return GL_STATIC_DRAW;
    case lgf::vtx_usage::stream_draw:
        return GL_STREAM_DRAW;
    }
    return 0;
}


inline auto to_gl(lgf::vtx_decl::type x)
    -> GLenum
{
    switch (x) {
    case lgf::vtx_decl::type::u8:
        return GL_UNSIGNED_BYTE;
    case lgf::vtx_decl::type::i8:
        return GL_BYTE;
    case lgf::vtx_decl::type::u16:
        return GL_UNSIGNED_SHORT;
    case lgf::vtx_decl::type::i16:
        return GL_SHORT;
    case lgf::vtx_decl::type::u32:
        return GL_UNSIGNED_INT;
    case lgf::vtx_decl::type::i32:
        return GL_INT;
    case lgf::vtx_decl::type::f32:
        return GL_FLOAT;
    case lgf::vtx_decl::type::none:
        return 0;
    }
    return 0;
}


inline auto to_gl(lgf::wrap_mode wm)
    -> GLenum
{
    switch (wm) {
    case lgf::wrap_mode::repeat:
        return GL_REPEAT;
    case lgf::wrap_mode::mirrored_repeat:
        return GL_MIRRORED_REPEAT;
    case lgf::wrap_mode::clamp_to_edge:
        return GL_CLAMP_TO_EDGE;
    case lgf::wrap_mode::clamp_to_border:
        return GL_CLAMP_TO_BORDER;
    }

    return 0;
}


inline auto to_gl(lgf::filter_mode fm)
    -> GLenum
{
    switch (fm) {
    case lgf::filter_mode::nearest:
        return GL_NEAREST;
    case lgf::filter_mode::linear:
        return GL_LINEAR;
    }

    return 0;
}

} /* lgf */

#endif
