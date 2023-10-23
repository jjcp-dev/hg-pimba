#ifndef LGF_IDX_BUFFER_HPP_NVNI7G3L
#define LGF_IDX_BUFFER_HPP_NVNI7G3L

#include <cstdint>

#include "cmm/span.hpp"

#include "./internal/id.hpp"
#include "./internal/handle_owner.hpp"


namespace lgf {

class idx_buffer_handle {
public:

    auto _internal() const noexcept
        -> void*
    {
        return m_ptr;
    }

protected:
    void* m_ptr;

    void destroy();
};


class idx_buffer : public lgf::idx_buffer_handle {
public:
    LGF_HANDLE_OWNER(idx_buffer, m_ptr)

    idx_buffer();

   ~idx_buffer();
};

} /* lgf */

#endif
