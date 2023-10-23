#ifndef LGF_VTX_RANGE_HPP_F2IW1LRM
#define LGF_VTX_RANGE_HPP_F2IW1LRM

namespace lgf {

class vtx_range {
public:

    constexpr vtx_range() = default;

    constexpr vtx_range(const vtx_range&) = default;

    constexpr vtx_range(vtx_range&&) = default;

    constexpr vtx_range(int start, int count)
        : m_start{start}, m_count{count}
    { }

    auto operator=(const vtx_range&) -> vtx_range& = default;

    auto operator=(vtx_range&&) -> vtx_range& = default;

    auto operator==(const vtx_range& rhs) const noexcept
        -> bool
    {
        return m_start == rhs.m_start and m_count == rhs.m_count;
    }

    auto operator!=(const vtx_range& rhs) const noexcept
        -> bool
    {
        return m_start != rhs.m_start or m_count != rhs.m_count;
    }

    auto start() const noexcept
        -> int
    {
        return m_start;
    }

    auto count() const noexcept
        -> int
    {
        return m_count;
    }

private:
    int m_start = 0;
    int m_count = 0;
};

} /* lgf */

#endif
