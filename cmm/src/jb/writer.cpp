#include <cstring>
#include <algorithm>

#include "cmm/jb/writer.hpp"
#include "cmm/mem/align.hpp"


struct header {
    std::uint32_t key;
    std::int32_t  value;
};


cmm::jb_writer::jb_writer(cmm::rspan buffer)
{
    if (cmm::align_of(buffer.data()) >= alignof(std::uint32_t))
    {
        m_begin = reinterpret_cast<char*>(buffer.data());
        m_head  = m_begin;
        m_end   = m_begin + buffer.size_bytes();
    }
}


bool cmm::jb_writer::write(std::uint32_t id, std::int32_t number)
{
    if (m_end - m_head < (int) sizeof(header))
        return false;

    auto h = reinterpret_cast<header*>(m_head);

    h->key = 0x01'00'00'00 | (id & 0x00'FF'FF'FF);
    h->value = number;

    m_head += sizeof(header);

    return true;
}


bool cmm::jb_writer::write(std::uint32_t id, float number)
{
    if (m_end - m_head < (int) sizeof(header))
        return false;

    auto h = reinterpret_cast<header*>(m_head);

    h->key = 0x02'00'00'00 | (id & 0x00'FF'FF'FF);
    h->value = *reinterpret_cast<std::int32_t*>(&number);

    m_head += sizeof(header);

    return true;
}


bool cmm::jb_writer::write(std::uint32_t id, const char* str)
{
    if (m_end - m_head < (int) sizeof(header) + 1)
        return false;

    auto h = reinterpret_cast<header*>(m_head);

    auto str_begin = m_head + sizeof(header);
    auto str_end   = m_head + sizeof(header);

    h->key = 0x03'00'00'00 | (id & 0x00'FF'FF'FF);

    while (*str)
    {
        if (str_end < m_end)
        {
            *str_end = *str;

            str_end++;
            str++;
        }
        else
        {
            return false;
        }
    }
    *str_end++ = 0;

    h->value = str_end - str_begin;

    m_head = std::min(cmm::align_forward(str_end, alignof(std::uint32_t)),
                      m_end);

    return true;
}


bool cmm::jb_writer::write(std::uint32_t id, cmm::cspan buffer)
{
    if (m_end - m_head < (int) sizeof(header) + buffer.size_bytes())
        return false;

    auto h = reinterpret_cast<header*>(m_head);

    h->key = 0x04'00'00'00 | (id & 0x00'FF'FF'FF);
    h->value = buffer.size_bytes();

    std::memcpy(m_head + sizeof(header), buffer.data(), buffer.size_bytes());

    auto aligned = cmm::align_forward(
        m_head + sizeof(header) + buffer.size_bytes(), alignof(std::uint32_t));

    m_head = std::min(aligned, m_end);

    return true;
}


bool cmm::jb_writer::write(std::uint32_t id, cmm::span<const std::int32_t> buffer)
{
    if (m_end - m_head < (int) sizeof(header) + buffer.size_bytes())
        return false;

    auto h = reinterpret_cast<header*>(m_head);

    h->key = 0x05'00'00'00 | (id & 0x00'FF'FF'FF);
    h->value = buffer.size_bytes();

    std::memcpy(m_head + sizeof(header), buffer.data(), buffer.size_bytes());

    m_head = m_head + sizeof(header) + buffer.size_bytes();

    return true;
}
