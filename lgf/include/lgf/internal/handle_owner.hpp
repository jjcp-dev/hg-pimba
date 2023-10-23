#ifndef LGF_HANDLE_OWNER_HPP_8BFW7QAP
#define LGF_HANDLE_OWNER_HPP_8BFW7QAP

#define LGF_HANDLE_OWNER(class_name) \
    class_name(const class_name&) = delete; \
    class_name(class_name&& e) { \
        m_id = e.m_id; \
        e.m_id = {}; \
    } \
    class_name& operator=(const class_name&) = delete; \
    class_name& operator=(class_name&& rhs) { \
        if (this != &rhs) { \
            destroy(); \
            m_id = rhs.m_id; \
            rhs.m_id = {}; \
        } \
        return *this; \
    }

#endif
