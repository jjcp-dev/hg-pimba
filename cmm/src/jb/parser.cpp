#include "cmm/jb/parser.hpp"
#include "cmm/mem/align.hpp"
#include <stdio.h>


static_assert(sizeof(float) == sizeof(std::int32_t),
              "`float` is expected to be a 32bit type");


struct header {
    std::uint32_t key;
    std::int32_t  value;
};


auto cmm::jb::next() noexcept
    -> cmm::jb::value
{
    const auto header_size = static_cast<int>(sizeof(header));

    printf("Check Header Size - ");
    if (m_buffer.size_bytes() < header_size)
    {
        printf("ERROR\n");
        return {};
    }
    printf("OK\n");

    auto h = reinterpret_cast<const header*>(m_buffer.data());

    const auto type = static_cast<jb::type>(h->key >> 24);  // last 8 bits

    if (type == jb::type::i32 or
        type == jb::type::f32)
    {
        printf("# i32 - f32\n");
        m_buffer = {h + 1, m_buffer.size() - header_size};

        return {h->key, {&h->value, (int) sizeof(std::int32_t)}};
    }
    else if (type == jb::type::bin or
             type == jb::type::str or
             type == jb::type::i32a)
    {
        printf("# bin - str - i32a\n");
        if (h->value < 0)
            return {};

        if (h->value == 0)
        {
            m_buffer = {h + 1, m_buffer.size() - header_size};

            return {h->key, {}};
        }

        auto end = m_buffer.data() + header_size + h->value;

        if (end > m_buffer.end())
            return {};

        if (type == jb::type::str)
        {
            // must be null terminated
            if (*(end - 1))
                return {};
        }

        auto aligned_end = cmm::align_forward(end, (int)alignof(std::int32_t));

        if (aligned_end <= m_buffer.end())
            m_buffer = {
                aligned_end, static_cast<int>(m_buffer.end() - aligned_end)
            };
        else
            m_buffer = {end, static_cast<int>(m_buffer.end() - end)};

        return {h->key, {h + 1, h->value}};
    }

    printf("Unknown Type\n");

    return {};
}
