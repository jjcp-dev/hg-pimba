#ifndef PMB_2D_SPRITE_SHEET_HPP_HAXF05LV
#define PMB_2D_SPRITE_SHEET_HPP_HAXF05LV

#include <cstddef>

#include <vector>
#include <algorithm>

#include "cmm/span.hpp"

#include "lgf/texture.hpp"

#include "./sprite.hpp"


namespace pmb {

class sprite_sheet {
public:

    sprite_sheet() = default;

    sprite_sheet(const sprite_sheet&) = delete;

    sprite_sheet(sprite_sheet&&) = default;

    sprite_sheet(lgf::texture&& texture, cmm::span<pmb::rect<short>> sprites)
    {
        m_texture = std::move(texture);
        m_sprites.resize(sprites.size());

        std::copy(sprites.begin(), sprites.end(), m_sprites.begin());
    }

    auto operator=(const sprite_sheet&)
        -> sprite_sheet& = delete;

    auto operator=(sprite_sheet&&)
        -> sprite_sheet& = default;

    auto operator[] (std::size_t index) const noexcept
        -> pmb::sprite
    {
        return {m_texture, m_sprites[index]};
    }

    auto size() const noexcept
        -> int
    {
        return m_sprites.size();
    }

    auto texture() const noexcept
        -> lgf::texture_handle
    {
        return m_texture;
    }

private:

    std::vector<pmb::rect<short>> m_sprites;
    lgf::texture                  m_texture;
};

} /* pmb */

#endif
