#ifndef LGF_SORT_KEY_HPP_FHCRUYUK
#define LGF_SORT_KEY_HPP_FHCRUYUK

#include <cstdint>


namespace lgf {

struct sort_key {
    std::uint32_t a = 0;
};


constexpr auto operator< (lgf::sort_key x, lgf::sort_key y)
    -> bool
{
    return x.a < y.a;
}


constexpr auto operator<= (lgf::sort_key x, lgf::sort_key y)
    -> bool
{
    return x.a <= y.a;
}


constexpr auto operator> (lgf::sort_key x, lgf::sort_key y)
    -> bool
{
    return x.a > y.a;
}


constexpr auto operator>= (lgf::sort_key x, lgf::sort_key y)
    -> bool
{
    return x.a >= y.a;
}


constexpr auto operator== (lgf::sort_key x, lgf::sort_key y)
    -> bool
{
    return x.a == y.a;
}

} /* lgf */

#endif
