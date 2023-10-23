#ifndef LGF_OPENGL_HPP_P1WCQE90
#define LGF_OPENGL_HPP_P1WCQE90

#include "glad/glad.h"


namespace lgf {

struct opengl_version {
    int major = 0;
    int minor = 0;
};


struct opengl_features {
    bool vertex_array_object = false;

    bool map_buffer = false;
};


class opengl {
public:

    static lgf::opengl_version  version;
    static lgf::opengl_features features;

    static bool init();
    static void shutdown();
};


} /* lgf */

#endif
