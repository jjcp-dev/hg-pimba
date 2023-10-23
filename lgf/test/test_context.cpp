#include "./test_context.hpp"

#include <cstdio>
#include <string>
#include <stdexcept>

#include "SDL.h"

#include "lgf/lgf.hpp"


lgf::test_context::test_context()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error{std::string{SDL_GetError()}};
    }

    auto window = SDL_CreateWindow("lgf-test-context",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   320,
                                   200,
                                   SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        throw std::runtime_error{std::string{SDL_GetError()}};
    }

    auto context = SDL_GL_CreateContext(window);

    if (context == nullptr)
    {
        throw std::runtime_error{std::string{SDL_GetError()}};
    }

    lgf::config cfg;

    cfg.log_fn = std::printf;
    cfg.log_err_fn = std::printf;

    lgf::init(cfg);
}


lgf::test_context::~test_context()
{
    lgf::shutdown();
    SDL_Quit();
}
