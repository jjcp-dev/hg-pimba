#include <cstdio>

#include "glm/gtc/matrix_transform.hpp"

#include "cmm/unused.hpp"

#include "lgf/shader.hpp"
#include "lgf/vtx_buffer.hpp"
#include "lgf/texture.hpp"
#include "lgf/command_list.hpp"
#include "lgf/lgf.hpp"

#include "stb_image.h"

#include "pmb/engine.hpp"
#include "pmb/2d/sprite_batcher.hpp"
#include "pmb/2d/sprite_sheet.hpp"
#include "pmb/2d/tilemap.hpp"
// #include "pmb/2d/anim_player.hpp"

#include "pmb/anim/clip.hpp"
#include "pmb/anim/cursor.hpp"

#include <chrono>


using namespace std::chrono_literals;


static auto coso(pmb::file_system* file_system)
    -> pmb::sprite_sheet
{
    static lgf::texture texture;
    // auto asset = file_system->read("tiles.png");
    auto asset = file_system->read("coso.png");

    if (asset.cspan().size() == 0)
    {
        return {};
    }

    lgf::texture_config cfg;
    cfg.min_filter = lgf::filter_mode::nearest;
    cfg.mag_filter = lgf::filter_mode::nearest;

    int x, y;
    auto image_data = stbi_load_from_memory(asset.cspan().data(),
                                            asset.cspan().size(),
                                            &x,
                                            &y,
                                            nullptr,
                                            4);
    lgf::image img;
    img.width = x;
    img.height = y;
    img.channels = 4;
    img.image_data = {image_data, x * y * 4};

    texture = lgf::texture{img, cfg};

    stbi_image_free(image_data);

    // std::vector<pmb::rect<short>> spr {{
    //     {16 * 0, 16 * 0, 16 + 16 * 0, 16 + 16 * 0},
    //     {16 * 1, 16 * 0, 16 + 16 * 1, 16 + 16 * 0},
    //     {16 * 2, 16 * 0, 16 + 16 * 2, 16 + 16 * 0},
    //     {16 * 3, 16 * 0, 16 + 16 * 3, 16 + 16 * 0},
    // }};

    std::vector<pmb::rect<short>> spr;
    for (int i = 0; i < 12; i++)
    {
        auto w = 165;
        auto h = 292;
        spr.emplace_back(w * i, h * 0, w + w * i, h + h * 0);
    }

    return {std::move(texture), spr};
}


void pmb::engine::update(std::chrono::nanoseconds dt)
{
    cmm::unused(dt);

    static auto s = shaders.get(
        pmb::shader_options::multi_textured_sprite);

    static auto ss = coso(file_system);
    static pmb::tilemap tm;

    // static pmb::animation_player player;

    // static pmb::basic_animation_track<short> anim_track;

    static std::vector<std::chrono::milliseconds> anim_times;
    static std::vector<short>                     anim_sprite_indices;

    static bool f = false;
    if (not f)
    {
        anim_sprite_indices.emplace_back(0);
        anim_times.emplace_back(16ms * 0 * 2);

        anim_sprite_indices.emplace_back(1);
        anim_times.emplace_back(16ms * 1 * 2);

        anim_sprite_indices.emplace_back(2);
        anim_times.emplace_back(16ms * 2 * 2);

        anim_sprite_indices.emplace_back(3);
        anim_times.emplace_back(16ms * 3 * 2);

        anim_sprite_indices.emplace_back(4);
        anim_times.emplace_back(16ms * 4 * 2);

        anim_sprite_indices.emplace_back(5);
        anim_times.emplace_back(16ms * 5 * 2);

        anim_sprite_indices.emplace_back(6);
        anim_times.emplace_back(16ms * 6 * 2);

        anim_sprite_indices.emplace_back(7);
        anim_times.emplace_back(16ms * 7 * 2);

        anim_sprite_indices.emplace_back(8);
        anim_times.emplace_back(16ms * 8 * 2);

        anim_sprite_indices.emplace_back(9);
        anim_times.emplace_back(16ms * 9 * 2);

        anim_sprite_indices.emplace_back(10);
        anim_times.emplace_back(16ms * 10 * 2);

        anim_sprite_indices.emplace_back(11);
        anim_times.emplace_back(16ms * 11 * 2);

        f = true;

        tm.m_sheet = std::move(ss);
        tm.m_columns = 10;
        tm.m_rows    = 1;
        tm.m_batcher = pmb::sprite_batcher{4};

        tm.m_map.push_back(0);
        tm.m_map.push_back(1);
        tm.m_map.push_back(2);
    }

    static pmb::anim::clip clp{anim_sprite_indices,
                               anim_times,
                               pmb::anim::interpolation::nearest};

    static pmb::anim::cursor anim_cursor{clp.duration(), pmb::anim::loop_mode::repeat};

    static auto ts_coso = resource.load_tileset("tileset.jb");

    tm.prep();

    lgf::draw_command dc;

    float tri[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         0.0f,  1.0f,
    };

    static auto vtx = lgf::vtx_buffer{lgf::vtx_usage::stream_draw,
                                      lgf::vtx_decl{
                                          {2, lgf::vtx_decl::type::f32},
                                      }, tri};

    static float a = 0.0f;
    // a += 0.01;

    // dc.vtx = vtx;
    // dc.vtx_range = {0, 3};
    dc.mvp = glm::perspective(glm::radians(45.0f), 900.f/600.f, 0.5f, 100.0f)
           // * glm::translate(glm::mat4(1.0f),
           //                  glm::vec3(0.0f, 5.0f, -45.0f + 2 * sinf(a)))
           // * glm::scale(glm::mat4(1.0f), glm::vec3(0.07f, -0.07f, 0.07f))
           * glm::translate(glm::mat4(1.0f),
                            glm::vec3(-16.0f, 1.0f, -45.0f + 2 * sinf(a)))
           * glm::scale(glm::mat4(1.0f), glm::vec3(1.f, 1.f, 1.f))
           ;

    // std::printf("frame: %i\n", player.current_frame());
    // player.advance(16ms);

    anim_cursor.advance(4ms);
    auto frame = clp.compute_frame<std::int16_t>(anim_cursor.current());

    tm.m_batcher.begin();

    // tm.m_batcher.add(tm.m_sheet[frame], {0.f, 0.f});
    tm.m_batcher.add(pmb::sprite{ts_coso.texture(), ts_coso[0]}, {0.f, 0.f});
    tm.m_batcher.add(pmb::sprite{ts_coso.texture(), ts_coso[1]}, {16.f, 0.f});
    tm.m_batcher.add(pmb::sprite{ts_coso.texture(), ts_coso[2]}, {32.f, 0.f});

    tm.m_batcher.add(pmb::sprite{ts_coso.texture(), ts_coso[0 + 16]}, {0.f,  -16.f});
    tm.m_batcher.add(pmb::sprite{ts_coso.texture(), ts_coso[1 + 16]}, {16.f, -16.f});
    tm.m_batcher.add(pmb::sprite{ts_coso.texture(), ts_coso[2 + 16]}, {32.f, -16.f});

    tm.m_batcher.end();

    dc.vtx = tm.m_batcher.vtx_buffer();
    dc.vtx_range = tm.m_batcher.vtx_range();

    dc.shader = s;
    // dc.textures[0] = tm.m_sheet.texture();
    dc.textures[0] = ts_coso.texture();


    static char* buffer = new char[1024];
    static lgf::command_list cmd{{buffer, 1024}};

    cmd.add({}, lgf::viewport{0, 0, 900, 600});
    cmd.add({}, lgf::clear_command{
        lgf::clear_mode::color, {1.0f, 0.0f, 1.0f}
    });
    cmd.add({}, dc);

    lgf::submit(cmd);
}


void pmb::engine::render()
{
}
