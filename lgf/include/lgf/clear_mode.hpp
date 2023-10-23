#ifndef LGF_CLEAR_MODE_HPP_NZPDEVFU
#define LGF_CLEAR_MODE_HPP_NZPDEVFU

#include "cmm/bit_ops.hpp"


namespace lgf {

CMM_DEFINE_BIT_OPERATORS(clear_mode)
enum class clear_mode {
    color = 1 << 0,
    depth = 1 << 1,
};

} /* lgf */

#endif
