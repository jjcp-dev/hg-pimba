#ifndef PMB_WRITER_HPP_GFCVIPD3
#define PMB_WRITER_HPP_GFCVIPD3

#include "../span.hpp"


namespace cmm {

class jb_writer {
public:

    jb_writer(cmm::rspan buffer);

    bool write(std::uint32_t id, std::int32_t number);

    bool write(std::uint32_t id, float number);

    bool write(std::uint32_t id, const char* str);

    bool write(std::uint32_t id, cmm::cspan buffer);

    bool write(std::uint32_t id, cmm::span<const std::int32_t> buffer);

    auto span() const noexcept
        -> cmm::cspan
    {
        return {m_begin, static_cast<int>(m_head - m_begin)};
    }

    auto span() noexcept
        -> cmm::rspan
    {
        return {m_begin, static_cast<int>(m_head - m_begin)};
    }

private:
    char* m_begin = nullptr;
    char* m_head = nullptr;
    char* m_end = nullptr;
};

} /* cmm */

#endif
