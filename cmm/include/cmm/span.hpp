#ifndef CMM_SPAN_HPP_EGULVQDL
#define CMM_SPAN_HPP_EGULVQDL

#include "./byte.hpp"


namespace cmm {

struct raw { };


template<typename T>
class span {
public:
    span() = default;
    span(const span&) = default;
    span(span&&) = default;
   ~span() = default;

    span(T* ptr, int size) noexcept
        : m_ptr{ptr}, m_size{size}
    { }

    template<int N>
    span(T (&array)[N]) noexcept
        : span(array, N)
    { }

    template<typename Container>
    span(Container& c)
        : span(c.data(), c.size())
    { }

    auto operator=(const span&) -> span& = default;
    auto operator=(span&&) -> span& = default;

    auto operator[](std::size_t index) noexcept
        -> T&
    {
        return m_ptr[index];
    }

    auto operator[](std::size_t index) const noexcept
        -> const T&
    {
        return m_ptr[index];
    }

    auto begin() noexcept
        -> T*
    {
        return m_ptr;
    }

    auto end() noexcept
        -> T*
    {
        return m_ptr + m_size;
    }

    auto begin() const noexcept
        -> const T*
    {
        return m_ptr;
    }

    auto end() const noexcept
        -> const T*
    {
        return m_ptr + m_size;
    }

    auto cbegin() const noexcept
        -> const T*
    {
        return m_ptr;
    }

    auto cend() const noexcept
        -> const T*
    {
        return m_ptr + m_size;
    }

    auto data() noexcept
        -> T*
    {
        return m_ptr;
    }

    auto data() const noexcept
        -> const T*
    {
        return m_ptr;
    }

    auto size() const noexcept
        -> int
    {
        return m_size;
    }

    auto size_bytes() const noexcept
        -> int
    {
        return m_size * sizeof(T);
    }

private:
    T*  m_ptr = nullptr;
    int m_size = 0;
};


template<>
class span<cmm::raw> {
public:
    span() = default;
    span(const span&) = default;
    span(span&&) = default;
   ~span() = default;

    template<typename T>
    span(T* ptr, int size) noexcept
        : m_ptr{reinterpret_cast<cmm::byte*>(ptr)}, m_size{size}
    { }

    template<typename T, int N>
    span(T (&array)[N]) noexcept
        : span(array, N * sizeof(T))
    { }

    template<typename Container>
    span(Container& c)
        : span(c.data(), static_cast<int>(c.size() * sizeof(*c.data())))
    { }

    auto operator=(const span&) -> span& = default;
    auto operator=(span&&) -> span& = default;

    auto operator[](std::size_t index) noexcept
        -> cmm::byte&
    {
        return m_ptr[index];
    }

    auto operator[](std::size_t index) const noexcept
        -> const cmm::byte&
    {
        return m_ptr[index];
    }

    auto begin() noexcept
        -> cmm::byte*
    {
        return m_ptr;
    }

    auto end() noexcept
        -> cmm::byte*
    {
        return m_ptr + m_size;
    }

    auto begin() const noexcept
        -> const cmm::byte*
    {
        return m_ptr;
    }

    auto end() const noexcept
        -> const cmm::byte*
    {
        return m_ptr + m_size;
    }

    auto cbegin() const noexcept
        -> const cmm::byte*
    {
        return m_ptr;
    }

    auto cend() const noexcept
        -> const cmm::byte*
    {
        return m_ptr + m_size;
    }

    auto data() noexcept
        -> cmm::byte*
    {
        return m_ptr;
    }

    auto data() const noexcept
        -> const cmm::byte*
    {
        return m_ptr;
    }

    auto size() const noexcept
        -> int
    {
        return m_size;
    }

    auto size_bytes() const noexcept
        -> int
    {
        return m_size;
    }

private:
    cmm::byte* m_ptr = nullptr;
    int        m_size = 0;
};


template<>
class span<const cmm::raw> {
public:
    span() = default;
    span(const span&) = default;
    span(span&&) = default;
   ~span() = default;

    template<typename T>
    span(T* ptr, int size) noexcept
        : m_ptr{reinterpret_cast<const cmm::byte*>(ptr)}, m_size{size}
    { }

    template<typename T, int N>
    span(T (&array)[N]) noexcept
        : span(array, N * sizeof(T))
    { }

    template<typename Container>
    span(Container& c)
        : span(c.data(), static_cast<int>(c.size() * sizeof(*c.data())))
    { }

    auto operator=(const span&) -> span& = default;
    auto operator=(span&&) -> span& = default;

    auto operator[](std::size_t index) const noexcept
        -> const cmm::byte&
    {
        return m_ptr[index];
    }

    auto begin() const noexcept
        -> const cmm::byte*
    {
        return m_ptr;
    }

    auto end() const noexcept
        -> const cmm::byte*
    {
        return m_ptr + m_size;
    }

    auto cbegin() const noexcept
        -> const cmm::byte*
    {
        return m_ptr;
    }

    auto cend() const noexcept
        -> const cmm::byte*
    {
        return m_ptr + m_size;
    }

    auto data() const noexcept
        -> const cmm::byte*
    {
        return m_ptr;
    }

    auto size() const noexcept
        -> int
    {
        return m_size;
    }

    auto size_bytes() const noexcept
        -> int
    {
        return m_size;
    }

private:
    const cmm::byte* m_ptr = nullptr;
    int              m_size = 0;
};


using rspan = cmm::span<cmm::raw>;
using cspan = cmm::span<const cmm::raw>;


template<typename T, int N>
auto make_span(T (&array)[N])
    -> cmm::span<T>
{
    return {array};
}


template<typename Container>
auto make_span(Container& c)
    -> cmm::span<typename Container::value_type>
{
    return {c.data(), c.size()};
}

} /* cmm */

#endif
