#ifndef PMB_ANIM_TRACK_HPP_MDQTLUPZ
#define PMB_ANIM_TRACK_HPP_MDQTLUPZ

#include <chrono>
#include "./clip.hpp"


namespace pmb {
namespace anim {

class track {
public:
    std::chrono::milliseconds offset;
    pmb::anim::clip           clip;
};

} /* anim */
} /* pmb */

#endif
