#include "SDL.h"

#include "gsl/gsl"

#include "lgf/lgf.hpp"
#include "pmb/engine.hpp"

#include "./file_system.hpp"


int main(int, char**)
{
    // SDL
    // ---------------------------------------------

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());

        return -1;
    }

    auto close_sdl = gsl::finally([] () {
        SDL_Quit();
    });

    auto window = SDL_CreateWindow("- app -",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   900,
                                   600,
                                   SDL_WINDOW_OPENGL |
                                   SDL_WINDOW_RESIZABLE |
                                   SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());

        return -1;
    }

    auto destroy_window = gsl::finally([&] () {
        SDL_DestroyWindow(window);
    });

    SDL_SetWindowMinimumSize(window, 320, 200);

    auto context = SDL_GL_CreateContext(window);

    if (context == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());

        return -1;
    }

    auto destroy_context = gsl::finally([&] () {
        SDL_GL_DeleteContext(context);
    });

    // lgf
    // ---------------------------------------------

    lgf::config cfg;

    cfg.log_fn = std::printf;
    cfg.log_err_fn = std::printf;

    if (not lgf::init(cfg))
        return -1;

    auto shutdown_lgf = gsl::finally([&] () {
        lgf::shutdown();
    });

    // pmb
    // ---------------------------------------------

    pimba::sdl::file_system fs;

    pmb::engine engine{&fs};

    // main loop
    // ---------------------------------------------

    while (true)
    {
        SDL_GL_SwapWindow(window);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_QUIT:
                return 0;
            }
        }

        engine.update({});
    }

    return 0;
}
