#ifndef LGF_SHADER_HPP_LSH4AW3V
#define LGF_SHADER_HPP_LSH4AW3V

#include "cmm/bit_ops.hpp"

#include "./internal/handle_owner.hpp"

#include "./shader_source.hpp"


namespace lgf {

class shader_handle {
public:
    using id_type = void*;

    explicit operator bool() const noexcept
    {
        return m_id != id_type{};
    }

    auto _id() noexcept
        -> id_type
    {
        return m_id;
    }

protected:
    id_type m_id = {};

    void destroy();
};


class shader : public lgf::shader_handle {
public:
    LGF_HANDLE_OWNER(shader)

    shader() = default;
    shader(lgf::opengl_shader_src);
   ~shader()
    {
        destroy();
    }
};

} /* lgf */

#endif
