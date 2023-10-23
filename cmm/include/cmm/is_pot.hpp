#ifndef CMM_IS_POT_HPP_WIB3VJR9
#define CMM_IS_POT_HPP_WIB3VJR9

namespace cmm {

/**
 * @brief Check that a given integer is a power of two.
 */
template<typename T>
constexpr bool is_pot(T n)
{
    return n && !(n & (n - 1));
}

} /* cmm */

#endif
