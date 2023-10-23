#ifndef PMB_SHADER_STORE_HPP_W2IPATLK
#define PMB_SHADER_STORE_HPP_W2IPATLK

#include "lgf/shader.hpp"


namespace pmb {

enum class shader_options {
    multi_textured_sprite
};


class shader_store {
public:

    auto get(pmb::shader_options opts) noexcept
        -> lgf::shader_handle
    {
        if (not m_mt_sprite)
            compile(opts);

        return m_mt_sprite;
    }

private:

    lgf::shader m_mt_sprite; ///< Multi textured sprite shader

    void compile(pmb::shader_options opts);
};

} /* pmb */

#endif
