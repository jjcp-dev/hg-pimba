#include <string>

#include "SDL.h"

#include "gsl/gsl"

#include "./file_system.hpp"


pimba::sdl::file_system::~file_system()
{
}


auto pimba::sdl::file_system::read(const char* path) const noexcept
    -> pmb::asset
{
    std::string asset_path;
    asset_path.reserve(256);

    asset_path += "assets/";
    asset_path += path;

    auto file = SDL_RWFromFile(asset_path.c_str(), "rb");

    if (not file)
        return {};

    auto close_file = gsl::finally([&] () {
        SDL_RWclose(file);
    });

    auto size = SDL_RWsize(file);
    if (size <= 0)
        return {};

    auto buffer = std::unique_ptr<char[]>{new char[size]};

    auto read_count = SDL_RWread(file, buffer.get(), 1, size);

    return {std::move(buffer), (int) read_count};
}
