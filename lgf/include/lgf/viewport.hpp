#ifndef LGF_VIEWPORT_HPP_CIX3N2RY
#define LGF_VIEWPORT_HPP_CIX3N2RY


namespace lgf {

class viewport {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    constexpr viewport(int x, int y, int w, int h)
        : x{x}, y{y}, w{w}, h{h}
    { }

    constexpr viewport(const viewport&) = default;
    constexpr viewport(viewport&&) = default;

    constexpr auto operator=(const viewport&)
        -> viewport& = default;

    constexpr auto operator=(viewport&&)
        -> viewport& = default;

    constexpr bool operator==(const viewport& rhs)
    {
        return (x == rhs.x) and (y == rhs.y) and
               (w == rhs.w) and (h == rhs.h);
    }
};

} /* lgf */

#endif
