#include "opengl.hpp"


lgf::opengl_version  lgf::opengl::version;
lgf::opengl_features lgf::opengl::features;


bool lgf::opengl::init()
{
    if (gladLoadGL())
    {
        version.major = GLVersion.major;
        version.minor = GLVersion.minor;

        if (version.major >= 3)
        {
            features.vertex_array_object = true;
            features.map_buffer = true;
        }

        return true;
    }

    return false;
}


void lgf::opengl::shutdown()
{
    // ...
}
