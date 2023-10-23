#ifndef CMM_MULTI_POOL_HPP_OIG3KLTN
#define CMM_MULTI_POOL_HPP_OIG3KLTN

#include <memory>
#include <vector>

#include "./mem/pool_allocator.hpp"


namespace cmm {

template<typename T, int Size>
class multi_pool {
    static_assert(Size >= 1, "Requires Size >= 1");
public:

    template<typename... Args>
    T* allocate(Args... args)
    {
        for (auto& p : m_pools)
        {
            if (not p.pool.is_full())
                return new (p.pool.allocate()) T{args...};
        }

        grow();

        return new (m_pools.back().pool.allocate()) T{args...};
    }

    void free(T* ptr)
    {
        for (int i = 0; i < int(m_pools.size()); i++)
        {
            auto& p = m_pools[i];

            auto k = reinterpret_cast<char*>(ptr);
            if (k >= p.buffer.get() and k <= p.end)
            {
                ptr->~T();

                p.pool.free(ptr);
                if (p.pool.is_empty())
                    m_pools.erase(m_pools.begin() + i);

                break;
            }
        }
    }

private:

    struct block {
        std::unique_ptr<char[]> buffer;
        void* end;
        cmm::pool_allocator pool;
    };

    std::vector<block> m_pools;

    void grow()
    {
        auto buffer_size = std::max(sizeof(T), sizeof(void*)) * Size;
        std::unique_ptr<char[]> buffer{new char[buffer_size]};

        auto ptr = buffer.get();
        auto size = int(buffer_size);

        m_pools.emplace_back(block{
            std::move(buffer),
            ptr + size,
            cmm::pool_allocator{ptr, size, (int)sizeof(T), (int)alignof(T)}
        });
    }
};

} /* cmm */

#endif
