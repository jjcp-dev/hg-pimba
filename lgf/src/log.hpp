#ifndef LGF_LOG_HPP_QMHDNV3I
#define LGF_LOG_HPP_QMHDNV3I

#include <exception>


namespace lgf {

extern int (*log)(const char* fmt, ...)
    __attribute__((format(printf, 1, 2)));

extern int (*log_err)(const char* fmt, ...)
    __attribute__((format(printf, 1, 2)));

#define LGF_FIXME() \
    lgf::log_err("FIXME: %s : %i\n", __FILE__, __LINE__); \
    std::terminate()

} /* lgf */

#endif
