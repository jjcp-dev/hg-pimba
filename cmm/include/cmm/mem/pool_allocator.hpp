#ifndef CMM_POOL_ALLOCATOR_HPP_KLWJXQKF
#define CMM_POOL_ALLOCATOR_HPP_KLWJXQKF

#include <cassert>
#include <cstdint>

#include <algorithm>

#include "../is_pot.hpp"


namespace cmm {

class pool_allocator {
public:

    pool_allocator(void* mem,
                   int size,
                   int block_size,
                   int block_alignment) noexcept
    {
        m_next = setup_linked_list(mem, size, block_size, block_alignment);
    }

    pool_allocator(cmm::pool_allocator&& p) noexcept
        : m_next{p.m_next}, m_alloc_count{p.m_alloc_count}
    {
        p.m_next = nullptr;
        p.m_alloc_count = 0;
    }

    auto operator=(cmm::pool_allocator&& rhs) noexcept
        -> cmm::pool_allocator&
    {
        if (this != &rhs)
        {
            m_next = rhs.m_next;
            m_alloc_count = rhs.m_alloc_count;

            rhs.m_next = nullptr;
            rhs.m_alloc_count = 0;
        }
        return *this;
    }

    auto allocate() noexcept
        -> void*
    {
        if (not m_next)
            return nullptr;

        auto ptr = m_next;
        m_next = reinterpret_cast<void**>(*m_next);
        m_alloc_count++;

        return ptr;
    }

    void free(void* ptr) noexcept
    {
        auto p = reinterpret_cast<char**>(ptr);
        *p = (char*)m_next;
        m_next = reinterpret_cast<void**>(p);

        if (m_alloc_count)
            m_alloc_count--;
    }

    bool is_full() const noexcept
    {
        return m_next == nullptr;
    }

    bool is_empty() const noexcept
    {
        return m_alloc_count == 0;
    }

private:
    void** m_next = nullptr;
    int    m_alloc_count = 0;

    auto setup_linked_list(void* mem, int size,
                           int block_size, int block_alignment)
        -> void**
    {
        assert(cmm::is_pot(block_alignment));

        block_alignment = std::max(block_alignment, (int) alignof(char*));
        block_size = std::max(block_size, (int) sizeof(char*));

        auto modulo = reinterpret_cast<std::uintptr_t>(mem) % block_alignment;
        auto offset = modulo ? block_alignment - int(modulo) : 0;

        if (size - offset >= block_size)
        {
            auto begin = reinterpret_cast<char*>(mem) + offset;
            size -= offset;

            char* head = begin;
            for (; head + block_size < begin + size; head += block_size)
                *reinterpret_cast<char**>(head) = head + block_size;
            *reinterpret_cast<char**>(head) = nullptr;

            return reinterpret_cast<void**>(begin);
        }
        return nullptr;
    }
};

} /* cmm */

#endif
