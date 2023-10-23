#ifndef LGF_IMAGE_HPP_QDZ5AEL2
#define LGF_IMAGE_HPP_QDZ5AEL2

#include "cmm/span.hpp"


namespace lgf {

class image {
public:
    int        width = 0;
    int        height = 0;
    int        channels = 0;
    cmm::cspan image_data;
};

} /* lgf */

#endif
