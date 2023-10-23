#ifndef LGF_BUFFER_ACCESS_HPP_4M0GIOCD
#define LGF_BUFFER_ACCESS_HPP_4M0GIOCD

#include "cmm/bit_ops.hpp"


namespace lgf {

CMM_DEFINE_BIT_OPERATORS(buffer_access)
enum class buffer_access {
    read  = 1 << 0,
    write = 1 << 1,
};

} /* lgf */

#endif
