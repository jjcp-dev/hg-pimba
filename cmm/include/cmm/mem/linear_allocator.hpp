#ifndef CMM_LINEAR_ALLOCATOR_HPP_ASP7M3GC
#define CMM_LINEAR_ALLOCATOR_HPP_ASP7M3GC

#include <cassert>

#include "./align.hpp"

#include "../span.hpp"


namespace cmm {

class linear_allocator {
public:

    linear_allocator(cmm::rspan buffer)
        : m_buffer{buffer},
          m_head{buffer.data()}
    { }

    auto allocate(int size, int alignment)
        -> void*
    {
        assert(cmm::is_pot(alignment));

        auto head = cmm::align_forward(m_head, alignment);

        if (m_buffer.data() + m_buffer.size() - head >= size)
        {
            m_head = head + size;
            return head;
        }

        return nullptr;
    }

    void free(void*)
    {
        /* do nothing */
    }

    void reset()
    {
        m_head = m_buffer.data();
    }

    auto capacity() const noexcept
        -> int
    {
        auto size = m_buffer.data() + m_buffer.size() - m_head;
        return static_cast<int>(size);
    }

private:
    cmm::rspan m_buffer;
    cmm::byte* m_head = nullptr;
};

} /* cmm */

#endif
