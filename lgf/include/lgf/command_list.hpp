#ifndef LGF_COMMAND_LIST_HPP_LSRAOECM
#define LGF_COMMAND_LIST_HPP_LSRAOECM

#include <new>
#include <utility>
#include <iterator>
#include <type_traits>

#include "cmm/span.hpp"
#include "cmm/mem/align.hpp"

#include "commands.hpp"
#include "sort_key.hpp"


namespace lgf {

/**
 * @brief
 */
class command_list {

    struct header {
        void*         command;
        lgf::sort_key key;
        command_type  type;
    };

    static_assert(std::is_trivially_destructible<header>::value,
                  "`header` must be `trivially_destructible`");

public:

    command_list(cmm::rspan buffer)
    {
        auto alignment = static_cast<int>(alignof(header));
        auto data      = reinterpret_cast<char*>(buffer.data());

        if (!data)
            return;

        m_begin = data;
        m_end   = cmm::align_backward(data + buffer.size_bytes(), alignment);

        m_left  = m_begin;
        m_right = m_end;
    }

    auto add(lgf::sort_key key, const lgf::clear_command&)
        -> bool;

    auto add(lgf::sort_key key, const lgf::viewport&)
        -> bool;

    auto add(lgf::sort_key key, const lgf::draw_command&)
        -> bool;

    void reset() noexcept
    {
        m_left  = m_begin;
        m_right = m_end;
    }

    auto begin() noexcept
        -> std::reverse_iterator<header*>
    {
        return std::reverse_iterator<header*>(
            reinterpret_cast<header*>(m_end)
        );
    }

    auto begin() const noexcept
        -> std::reverse_iterator<const header*>
    {
        return std::reverse_iterator<const header*>(
            reinterpret_cast<const header*>(m_end)
        );
    }

    auto cbegin() const noexcept
        -> std::reverse_iterator<const header*>
    {
        return std::reverse_iterator<const header*>(
            reinterpret_cast<const header*>(m_end)
        );
    }

    auto end() noexcept
        -> std::reverse_iterator<header*>
    {
        return std::reverse_iterator<header*>(
            reinterpret_cast<header*>(m_right)
        );
    }

    auto end() const noexcept
        -> std::reverse_iterator<const header*>
    {
        return std::reverse_iterator<const header*>(
            reinterpret_cast<const header*>(m_right)
        );
    }

    auto cend() const noexcept
        -> std::reverse_iterator<const header*>
    {
        return std::reverse_iterator<const header*>(
            reinterpret_cast<const header*>(m_right)
        );
    }

private:
    char* m_begin = nullptr;
    char* m_end   = nullptr;
    char* m_left  = nullptr;
    char* m_right = nullptr;

    template<typename T, typename... Args>
    auto allocate(lgf::sort_key, lgf::command_type, Args&&...)
        -> T*;
};

} /* lgf */

#endif
