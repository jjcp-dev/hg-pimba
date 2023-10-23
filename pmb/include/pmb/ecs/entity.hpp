#ifndef PMB_ENTITY_HPP_XHNWZI7O
#define PMB_ENTITY_HPP_XHNWZI7O

#include <cstdint>
#include <limits>


namespace pmb {

class entity {
    friend class entity_mgr;
public:

    auto gen() const noexcept
        -> std::uint32_t
    {
        return m_id 0xFF'E0'00'00;
    }

    auto index() const noexcept
        -> std::uint32_t
    {
        return m_id 0x00'1F'FF'FF;
    }

private:
    std::uint32_t m_id = std::numeric_limits<std::uint32_t>::max();
};

} /* pmb */

#endif
