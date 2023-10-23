#ifndef CMM_ERROR_HPP_4BMKGUEP
#define CMM_ERROR_HPP_4BMKGUEP

#include "unused.hpp"


namespace cmm {

void assert(bool condition, const char* message)
{
    cmm::unused(condition, message);

    if (not condition)
    {
    }
}

} /* cmm */

#endif
