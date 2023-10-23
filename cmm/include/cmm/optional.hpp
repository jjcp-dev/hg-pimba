#ifndef CMM_OPTIONAL_HPP_FUEBCPWU
#define CMM_OPTIONAL_HPP_FUEBCPWU

#include <new>
#include <utility>

#include <cassert>


namespace cmm {

template<typename T>
class optional {
public:
    optional() = default;

    optional(const optional& o)
    {
        if (o.m_valid)
            new (&m_data) T{o.m_data};

        m_valid = o.m_valid;
    }

    optional(optional&& o)
    {
        if (o.m_valid)
            new (&m_data) T{std::move(o.m_data)};

        m_valid = o.m_valid;
    }

    optional(T&& d)
    {
        new (&m_data) T{std::move(d)};
        m_valid = true;
    }

    optional(const T& d)
    {
        new (&m_data) T{d};
        m_valid = true;
    }

    template<typename ...Args>
    optional(Args... args)
    {
        new (&m_data) T{args...};
        m_valid = true;
    }

   ~optional()
    {
        if (m_valid)
            m_data.~T();
    }

    auto operator=(const optional& rhs)
        -> optional&
    {
        if (this != &rhs)
        {
            if (rhs.m_valid)
            {
                if (m_valid)
                {
                    m_data = rhs.m_data;
                }
                else
                {
                    new (&m_data) T{rhs.m_data};
                    m_valid = true;
                }
            }
            else
            {
                if (m_valid)
                {
                    m_data.~T();
                    m_valid = false;
                }
            }
        }
        return *this;
    }

    auto operator=(optional&& rhs)
        -> optional&
    {
        if (this != &rhs)
        {
            if (rhs.m_valid)
            {
                if (m_valid)
                {
                    m_data = std::move(rhs.m_data);
                }
                else
                {
                    new (&m_data) T{std::move(rhs.m_data)};
                    m_valid = true;
                }
            }
            else
            {
                if (m_valid)
                {
                    m_data.~T();
                    m_valid = false;
                }
            }
        }
        return *this;
    }

    explicit operator bool() const noexcept
    {
        return m_valid;
    }

    auto is_valid() const noexcept
        -> bool
    {
        return m_valid;
    }

    auto value() const noexcept
        -> const T&
    {
        assert(m_valid);

        return m_data;
    }

    auto value() noexcept
        -> T&
    {
        assert(m_valid);

        return m_data;
    }

private:
    union {
        T    m_data;
        char _dummy;
    };
    bool m_valid = false;
};

} /* cmm */

#endif
