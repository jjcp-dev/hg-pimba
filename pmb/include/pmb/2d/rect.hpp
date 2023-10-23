#ifndef PMB_2D_RECT_HPP_FVHKJIZN
#define PMB_2D_RECT_HPP_FVHKJIZN

namespace pmb {

template<typename T>
class rect {
public:
    T x0 = {};
    T y0 = {};
    T x1 = {};
    T y1 = {};

    constexpr rect() = default;
    constexpr rect(T x0, T y0, T x1, T y1)
        : x0{x0}, y0{y0}, x1{x1}, y1{y1}
    { }

    constexpr auto operator==(const rect& r) const
        -> bool
    {
        return x0 == r.x0 and
               y0 == r.y0 and
               x1 == r.x1 and
               y1 == r.y1;
    }

    constexpr auto operator!=(const rect& r) const
        -> bool
    {
        return not (*this == r);
    }
};

} /* pmb */

#endif
