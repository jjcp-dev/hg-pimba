#include "pmb/anim/clip.hpp"


auto pmb::anim::clip::compute_indices(std::chrono::milliseconds time) noexcept
    -> std::pair<int, int>
{
    assert(m_size > 0);

    if (time > m_times[m_lookup_hint])
    {
        for (int i = m_lookup_hint + 1; i < m_size; ++i)
        {
            if (time < m_times[i])
            {
                m_lookup_hint = i;
                return {i - 1, i};
            }
        }

        auto last = m_size - 1;

        m_lookup_hint = last;
        return {last, last};
    }
    else if (time < m_times[m_lookup_hint])
    {
        for (int i = m_lookup_hint - 1; i >= 0; --i)
        {
            if (time >= m_times[i])
            {
                m_lookup_hint = i;
                return {i, i + 1};
            }
        }

        m_lookup_hint = 0;
        return {0, 0};
    }
    else
    {
        return {m_lookup_hint, m_lookup_hint};
    }
}
