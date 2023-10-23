#ifndef CMM_BIT_OPS_HPP_U5OWL4K1
#define CMM_BIT_OPS_HPP_U5OWL4K1

#include <type_traits>


#define CMM_DEFINE_BIT_OPERATORS(E) \
    enum class E; \
    inline E operator & (E x, E y) { \
        return static_cast<E>( \
            static_cast<typename std::underlying_type<E>::type>(x) & \
            static_cast<typename std::underlying_type<E>::type>(y)); \
    } \
    inline E operator | (E x, E y) { \
        return static_cast<E>( \
            static_cast<typename std::underlying_type<E>::type>(x) | \
            static_cast<typename std::underlying_type<E>::type>(y)); \
    } \
    inline E operator ^ (E x, E y) { \
        return static_cast<E>( \
            static_cast<typename std::underlying_type<E>::type>(x) ^ \
            static_cast<typename std::underlying_type<E>::type>(y)); \
    } \
    inline E operator ~ (E x) { \
        return static_cast<E>( \
            ~static_cast<typename std::underlying_type<E>::type>(x)); \
    } \
    inline E& operator &= (E& x, E y) { x = x & y; return x; } \
    inline E& operator |= (E& x, E y) { x = x | y; return x; } \
    inline E& operator ^= (E& x, E y) { x = x ^ y; return x; }


namespace cmm {

template<typename E>
constexpr bool any(E x)
{
    using T = typename std::underlying_type<E>::type;
    return bool(static_cast<T>(x));
}

} /* cmm */

#endif
