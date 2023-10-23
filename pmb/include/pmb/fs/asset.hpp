#ifndef PMB_FS_ASSET_HPP_QPM7PJKD
#define PMB_FS_ASSET_HPP_QPM7PJKD

#include <cassert>
#include <memory>

#include "cmm/span.hpp"


namespace pmb {

class asset {
public:

    asset() = default;

    asset(cmm::cspan v) noexcept
    {
        m_buffer = (const char*) v.data();
        m_size   = v.size_bytes();
        m_owned  = false;
    }

    asset(asset&& a) noexcept
    {
        m_buffer = a.m_buffer;
        m_size   = a.m_size;
        m_owned  = a.m_owned;

        a.m_owned = false;
    }

    asset(std::unique_ptr<char[]> ptr, int size) noexcept
    {
        m_buffer = ptr.release();
        m_size   = size;
        m_owned  = true;
    }

   ~asset()
    {
        if (m_owned)
            delete[] m_buffer;
    }

    auto cspan() const noexcept
        -> cmm::cspan
    {
        return {m_buffer, m_size};
    }

private:
    const char* m_buffer = nullptr;
    int         m_size   = 0;
    bool        m_owned  = false;
};

} /* pmb */

#endif
