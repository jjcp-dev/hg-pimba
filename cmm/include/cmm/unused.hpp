#ifndef CMM_UNUSED_HPP_ZLFRNBYD
#define CMM_UNUSED_HPP_ZLFRNBYD

namespace cmm {

/**
 * @brief Simple template function to suppress `unused variable` warnings
 *
 * Just pass any number of variables you are not using into this function to
 * hopefully suppress any `unused variable` warnings.
 */
template<typename ...T>
void unused(T&&...)
{
    /* do nothing */
}

} /* cmm */

#endif
