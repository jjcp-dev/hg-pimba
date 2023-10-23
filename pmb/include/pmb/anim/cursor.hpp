#ifndef PMB_ANIMATION_CURSOR_HPP_OCZRLTEG
#define PMB_ANIMATION_CURSOR_HPP_OCZRLTEG

#include <chrono>


namespace pmb {
namespace anim {

enum class loop_mode {
    single, ///< play once, don't repeat
    repeat, ///< infinite loop
    bounce, ///< loop back and forth
};


class cursor {
public:

    cursor() = default;

    cursor(std::chrono::milliseconds duration,
           pmb::anim::loop_mode      mode) noexcept
        : m_duration{duration},
          m_mode{mode}
    { }

    cursor(const cursor&) = default;

    cursor(cursor&&) = default;

    auto operator=(const cursor&)
        -> cursor& = default;

    auto operator=(cursor&&)
        -> cursor& = default;

    auto advance(std::chrono::milliseconds dt) noexcept
        -> std::chrono::milliseconds
    {
        switch (m_mode) {
        case pmb::anim::loop_mode::single:
            m_current = m_current + dt > m_duration ? m_duration
                                                    : m_current + dt;
            return m_current;

        case pmb::anim::loop_mode::repeat:
            m_current = (m_current + dt) % m_duration;

            return m_current;

        case pmb::anim::loop_mode::bounce:
            m_current += m_direction * dt;

            if (m_current >= m_duration)
            {
                m_current = m_duration - (m_current % m_duration);
                m_direction = -1;
            }
            else if (m_current <= std::chrono::milliseconds{0})
            {
                m_current = -m_current % m_duration;
                m_direction = 1;
            }

            return m_current;
        }

        return m_current;
    }

    auto current() const noexcept
        -> std::chrono::milliseconds
    {
        return m_current;
    }

    auto duration() const noexcept
        -> std::chrono::milliseconds
    {
        return m_duration;
    }

    auto loop_mode() const noexcept
        -> pmb::anim::loop_mode
    {
        return m_mode;
    }

    auto direction() const noexcept
        -> int
    {
        return m_direction;
    }

private:

    std::chrono::milliseconds m_duration{0};
    std::chrono::milliseconds m_current {0};

    pmb::anim::loop_mode      m_mode      = pmb::anim::loop_mode::single;
    int                       m_direction = 1;
};

} /* anim */
} /* pmb */

#endif
