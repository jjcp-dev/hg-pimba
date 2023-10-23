#ifndef LGF_VTX_BUFFER_HPP_AHTJYJ2Q
#define LGF_VTX_BUFFER_HPP_AHTJYJ2Q

#include "cmm/span.hpp"

#include "internal/handle_owner.hpp"

#include "vtx_usage.hpp"
#include "vtx_decl.hpp"
#include "buffer_access.hpp"


namespace lgf {

/**
 * @brief Non-owning vertex buffer handle
 */
class vtx_buffer_handle {
public:
    using id_type = void*;

    auto usage() const noexcept
        -> lgf::vtx_usage;

    auto decl() const noexcept
        -> const lgf::vtx_decl&;

    auto map(lgf::buffer_access) noexcept
        -> cmm::rspan;

    auto unmap() noexcept
        -> bool;

    auto _id()
        -> id_type
    {
        return m_id;
    }

protected:
    id_type m_id = {};

    void destroy() noexcept;
};


class vtx_buffer : public lgf::vtx_buffer_handle {
public:
    LGF_HANDLE_OWNER(vtx_buffer);

    vtx_buffer() = default;

    vtx_buffer(lgf::vtx_usage usage,
               lgf::vtx_decl  decl,
               int            count) noexcept;

    vtx_buffer(lgf::vtx_usage usage,
               lgf::vtx_decl  decl,
               cmm::cspan     buffer_data) noexcept;

   ~vtx_buffer() noexcept;
};

} /* lgf */

#endif
