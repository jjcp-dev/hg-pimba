#include "./log.hpp"


int (*lgf::log)(const char* fmt, ...);

int (*lgf::log_err)(const char* fmt, ...);
