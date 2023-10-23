#ifndef LGF_VTX_DECL_HPP_BTKK4ODY
#define LGF_VTX_DECL_HPP_BTKK4ODY

#include <cassert>
#include <cstdint>

#include <initializer_list>
#include <algorithm>


namespace lgf {

/**
 * @brief Vertex format declaration
 */
class vtx_decl {
public:

    enum class type : std::uint8_t {
        none = 0,
        i8   = 1, ///< signed 8-bit number
        u8   = 2, ///< unsigned 8-bit number
        i16  = 3, ///< signed 16-bit number
        u16  = 4, ///< unsigned 16-bit number
        i32  = 5, ///< signed 32-bit number
        u32  = 6, ///< unsigned 32-bit numberstdio.h
        f32  = 7, ///< 32-bit float
    };

    class slot {
    public:

        slot() = default;

        slot(const slot&) = default;

        slot(slot&&) = default;

        slot(int count, bool normalize, vtx_decl::type type)
        {
            assert(count >= 1 and count <= 4);

            m_count = (normalize ? 0b1000'0000 : 0) | (count & 0x0F);
            m_type = type;
        }

        slot(int count, vtx_decl::type type)
            : slot(count, false, type)
        { }

        auto operator=(const slot&) -> slot& = default;

        auto operator=(slot&&) -> slot& = default;

        bool operator==(slot rhs) const noexcept
        {
            return m_count == rhs.m_count and m_type == rhs.m_type;
        }

        bool operator!=(slot rhs) const noexcept
        {
            return not (*this == rhs);
        }

        auto count() const noexcept
            -> int
        {
            return m_count & 0x0F;
        }

        auto type() const noexcept
            -> vtx_decl::type
        {
            return m_type;
        }

        auto normalized() const noexcept
            -> bool
        {
            return m_count & 0b1000'0000;
        }

    private:
        std::uint8_t   m_count = 0;
        vtx_decl::type m_type  = vtx_decl::type::none;
    };

    vtx_decl() = default;
    vtx_decl(std::initializer_list<slot> slots)
    {
        assert(slots.size() <= 8);

        m_top = static_cast<int>(slots.size());
        for (int i = 0; i < m_top; i++)
        {
            m_slots[i] = slots.begin()[i];

            switch (m_slots[i].type()) {
            case type::u8:
            case type::i8:
                m_stride += 1 * m_slots[i].count();
                break;
            case type::u16:
            case type::i16:
                m_stride += 2 * m_slots[i].count();
                break;
            case type::u32:
            case type::i32:
            case type::f32:
                m_stride += 4 * m_slots[i].count();
                break;
            case type::none:
                break;
            }
        }
    }

    auto operator[](int index) noexcept
        -> slot&
    {
        return m_slots[index];
    }

    auto operator[](int index) const noexcept
        -> const slot&
    {
        return m_slots[index];
    }

    bool operator==(const vtx_decl& rhs) const noexcept
    {
        return m_top == rhs.m_top and std::equal(begin(), end(), rhs.begin());
    }

    bool operator!=(const vtx_decl& rhs) const noexcept
    {
        return m_top != rhs.m_top or not std::equal(begin(), end(), rhs.begin());
    }

    auto size() const noexcept
        -> int
    {
        return m_top;
    }

    auto stride() const noexcept
        -> int
    {
        return m_stride;
    }

    auto begin() const noexcept
        -> const slot*
    {
        return m_slots;
    }

    auto cbegin() const noexcept
        -> const slot*
    {
        return m_slots;
    }

    auto end() const noexcept
        -> const slot*
    {
        return m_slots + m_top;
    }

    auto cend() const noexcept
        -> const slot*
    {
        return m_slots + m_top;
    }

private:
    slot m_slots[8];
    int  m_top = 0;
    int  m_stride = 0;
};

} /* lgf */

#endif
