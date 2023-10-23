#ifndef CMM_BIN_BUFFER_HPP_QI5KDETC
#define CMM_BIN_BUFFER_HPP_QI5KDETC

#include <cstddef>
#include <memory>
#include "./byte.hpp"


namespace cmm {

class buffer {
public:

    explicit buffer(std::size_t size)
        : m_ptr{new cmm::byte[size]},
          m_size{size}
    { }

    auto data() noexcept
        -> cmm::byte*
    {
        return m_ptr.get();
    }

    auto data() const noexcept
        -> const cmm::byte*
    {
        return m_ptr.get();
    }

    auto size() const noexcept
        -> std::size_t
    {
        return m_size;
    }

    auto begin() noexcept
        -> cmm::byte*
    {
        return m_ptr.get();
    }

    auto end() noexcept
        -> cmm::byte*
    {
        return m_ptr.get() + m_size;
    }

    auto begin() const noexcept
        -> const cmm::byte*
    {
        return m_ptr.get();
    }

    auto end() const noexcept
        -> const cmm::byte*
    {
        return m_ptr.get() + m_size;
    }

    auto cbegin() const noexcept
        -> const cmm::byte*
    {
        return m_ptr.get();
    }

    auto cend() const noexcept
        -> const cmm::byte*
    {
        return m_ptr.get() + m_size;
    }

private:
    std::unique_ptr<cmm::byte[]> m_ptr;
    std::size_t                  m_size = 0;
};

} /* cmm */

#endif
