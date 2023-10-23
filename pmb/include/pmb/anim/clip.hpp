#ifndef PMB_ANIM_CLIP_HPP_LYZIZCGD
#define PMB_ANIM_CLIP_HPP_LYZIZCGD

#include <cassert>

#include <algorithm>
#include <chrono>
#include <numeric>
#include <utility>

#include "cmm/span.hpp"


namespace pmb {
namespace anim {

enum class interpolation {
    nearest,
    linear,
};


enum class frame_type {
    i16
};


class clip {
public:

    clip(cmm::span<const std::int16_t>              frames,
         cmm::span<const std::chrono::milliseconds> times,
         pmb::anim::interpolation                   mode)
        : m_frames{frames.data()},
          m_times{times.data()},
          m_size{std::min(times.size(), frames.size())},
          m_mode{mode},
          m_frame_type{pmb::anim::frame_type::i16}
    {}

    auto type() const noexcept
        -> pmb::anim::frame_type
    {
        return m_frame_type;
    }

    auto size() const noexcept
        -> int
    {
        return m_size;
    }

    auto duration() const noexcept
        -> std::chrono::milliseconds
    {
        if (m_size)
            return m_times[m_size - 1];

        return std::chrono::milliseconds{0};
    }

    auto compute_indices(std::chrono::milliseconds time) noexcept
        -> std::pair<int, int>;

    template<typename T>
    auto compute_frame(std::chrono::milliseconds time) noexcept
        -> T
    {
        auto indices = compute_indices(time);

        auto t0 = m_times[indices.first];
        auto t1 = m_times[indices.second];

        auto frames = reinterpret_cast<const T*>(m_frames);

        auto& f0 = frames[indices.first];
        auto& f1 = frames[indices.second];

        auto alpha = (t1 - t0).count()
                   ? (float) (time - t0).count() / (t1 - t0).count()
                   : 0.f;

        switch (m_mode) {
        case pmb::anim::interpolation::nearest:
            return time - t0 <= t1 - time ? f0 : f1;

        case pmb::anim::interpolation::linear:
            return static_cast<T>(f1 * alpha + f0 * (1 - alpha));
        }

        return {};
    }

private:
    const void*                      m_frames = nullptr;
    const std::chrono::milliseconds* m_times  = nullptr;
    const int                        m_size   = 0;

    const pmb::anim::interpolation   m_mode;
    const pmb::anim::frame_type      m_frame_type;
    int                              m_lookup_hint = 0;
};

} /* anim */
} /* pmb */

#endif
