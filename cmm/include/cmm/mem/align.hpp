#ifndef CMM_MEM_ALIGN_HPP_8Y7OVUFV
#define CMM_MEM_ALIGN_HPP_8Y7OVUFV

#include <cstdint>
#include <cassert>

#include "../is_pot.hpp"


namespace cmm {

inline auto forward_alignment_offset(const void* ptr, int alignment)
    -> int
{
    assert(cmm::is_pot(alignment));

    auto modulo = reinterpret_cast<std::uintptr_t>(ptr) & (alignment - 1);
    return modulo ? alignment - int(modulo) : 0;
}


template<typename T>
inline auto align_forward(const T* ptr, int alignment)
    -> const T*
{
    auto offset = cmm::forward_alignment_offset(ptr, alignment);

    return reinterpret_cast<const T*>(
        reinterpret_cast<const char*>(ptr) + offset
    );
}


template<typename T>
inline auto align_forward(T* ptr, int alignment)
    -> T*
{
    auto offset = cmm::forward_alignment_offset(ptr, alignment);

    return reinterpret_cast<T*>(
        reinterpret_cast<char*>(ptr) + offset
    );
}


template<typename T>
inline auto align_forward(T* ptr)
    -> T*
{
    return align_forward(ptr, alignof(T));
}


template<typename T>
inline auto align_backward(T* ptr, int alignment)
    -> T*
{
    assert(cmm::is_pot(alignment));

    auto p = reinterpret_cast<std::uintptr_t>(ptr);

    return reinterpret_cast<T*>(p & ~(alignment - 1));
}


template<typename T>
inline auto align_backward(T* ptr)
    -> T*
{
    return cmm::align_backward(ptr, alignof(T));
}


inline auto align_of(const void* ptr)
    -> std::size_t
{
    auto n = reinterpret_cast<std::uintptr_t>(ptr);
    return (n & (n - 1)) ^ n;
}

} /* cmm */

#endif
