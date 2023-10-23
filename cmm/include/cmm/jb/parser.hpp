#ifndef CMM_JB_PARSER_HPP_GBC8HKOS
#define CMM_JB_PARSER_HPP_GBC8HKOS

#include <cassert>
#include <cstdint>

#include "../mem/align.hpp"

#include "../span.hpp"


namespace cmm {

class jb {
public:

    enum class type {
        none  = 0,
        i32   = 1,
        f32   = 2,
        str   = 3,
        bin   = 4,
        i32a  = 5,
    };

    class value {
        friend class jb;
    public:

        value() = default;

        auto id() const noexcept
            -> std::int32_t
        {
            return static_cast<std::int32_t>(m_key & 0x00'FF'FF'FF);
        }

        auto type() const noexcept
            -> jb::type
        {
            return static_cast<jb::type>(m_key >> 24);
        }

        auto as_string() const noexcept
            -> const char*
        {
            assert(type() == jb::type::str);
            return (const char*) m_value.data();
        }

        auto as_string_span() const noexcept
            -> cmm::span<const char>
        {
            assert(type() == jb::type::str);
            return {reinterpret_cast<const char*>(m_value.data()),
                    m_value.size_bytes()};
        }

        auto as_float() const noexcept
            -> float
        {
            assert(type() == jb::type::f32);
            return *reinterpret_cast<const float*>(m_value.data());
        }

        auto as_int32() const noexcept
            -> std::int32_t
        {
            assert(type() == jb::type::i32);
            return *reinterpret_cast<const std::int32_t*>(m_value.data());
        }

        auto as_int32_array() const noexcept
            -> cmm::span<const std::int32_t>
        {
            assert(type() == jb::type::i32a);
            return {reinterpret_cast<const std::int32_t*>(m_value.data()),
                    static_cast<int>(m_value.size_bytes() / sizeof(std::int32_t))};
        }

        auto as_binary() const noexcept
            -> cmm::span<const cmm::byte>
        {
            assert(type() == jb::type::bin);
            return {reinterpret_cast<const cmm::byte*>(m_value.data()),
                    m_value.size_bytes()};
        }

        auto as_binary() noexcept
            -> cmm::span<const cmm::byte>
        {
            assert(type() == jb::type::bin);
            return {reinterpret_cast<const cmm::byte*>(m_value.data()),
                    m_value.size_bytes()};
        }

    private:
        cmm::cspan    m_value;
        std::uint32_t m_key;

        value(std::uint32_t key, cmm::cspan value)
            : m_value{value}, m_key{key}
        { }
    };

    jb(cmm::cspan buffer)
    {
        if (cmm::align_of(buffer.data()) >= alignof(std::int32_t))
            m_buffer = buffer;
    }

    auto next() noexcept
        -> value;

    template<typename Function>
    void for_each(Function f)
    {
        for (auto v = next(); v.type() != type::none; v = next())
            f(v);
    }

private:
    cmm::cspan m_buffer;
};

} /* cmm */

#endif
