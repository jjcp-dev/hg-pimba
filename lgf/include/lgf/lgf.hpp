#ifndef LGF_LGF_HPP_6MKCJJ8Q
#define LGF_LGF_HPP_6MKCJJ8Q

#include "command_list.hpp"


namespace lgf {

using log_t = int (*)(const char* fmt, ...);
using log_err_t =  int (*)(const char* fmt, ...);


struct config {
    log_t     log_fn;
    log_err_t log_err_fn;
};


bool init(const config&);

void shutdown();

void submit(lgf::command_list&);

} /* lgf */

#endif
