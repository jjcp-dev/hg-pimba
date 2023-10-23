#ifndef CMM_RESULT_HPP_R3QYF1KS
#define CMM_RESULT_HPP_R3QYF1KS

#include <cassert>
#include <new>


namespace cmm {

namespace detail {
    template<typename T> struct ok_wrapper { T value; };
    template<typename E> struct err_wrapper { E error; };
}


template<typename T, typename E>
class result {
public:

    result(cmm::detail::ok_wrapper<T>&& ok)
    {
        new (&m_value) T{std::forward<T>(ok.value)};

        m_is_valid = true;
    }

    result(cmm::detail::err_wrapper<E>&& err)
    {
        new (&m_error) E{std::forward<E>(err.error)};

        m_is_valid = false;
    }

    result(const result& r)
    {
        m_is_valid = r.m_is_valid;

        if (r.m_is_valid)
            new (&m_value) T{r.m_value};
        else
            new (&m_error) E{r.m_error};
    }

    result(result&& r)
    {
        m_is_valid = r.m_is_valid;

        if (r.m_is_valid)
            new (&m_value) T{std::move(r.m_value)};
        else
            new (&m_error) E{std::move(r.m_error)};
    }

   ~result()
    {
        destroy();
    }

    auto is_valid() const noexcept
    {
        return m_is_valid;
    }

    auto value() const -> const T&
    {
        assert(m_is_valid);

        return m_value;
    }

    auto error() const -> const E&
    {
        assert(not m_is_valid);

        return m_error;
    }

private:
    union {
        T m_value;
        E m_error;
    };
    bool m_is_valid = false;

    void destroy()
    {
        if (m_is_valid)
            m_value.~T();
        else
            m_error.~E();
    }
};


template<typename T>
auto ok(T&& value)
{
    return cmm::detail::ok_wrapper<typename std::remove_reference<T>::type>{std::forward<T>(value)};
}


template<typename E>
auto err(E&& error)
{
    return cmm::detail::err_wrapper<typename std::remove_reference<E>::type>{std::forward<E>(error)};
}

} /* cmm */

#endif
