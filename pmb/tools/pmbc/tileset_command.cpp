#include <fstream>
#include <cstdio>

#include "docopt.h"
#include "nlohmann/json.hpp"

#include "pmb/formats/tileset.hpp"

#include "./tileset_command.hpp"
#include "./tiled.hpp"


using json = nlohmann::json;


static auto USAGE = R"(
Usage:
    pmbc-tileset [options] <input> <output>

Arguments:
    input         Path to a Tiled JSON tileset file.
    output        Output file path.

Options:
    -i --info     Print tileset information.
    -h --help     Show this screen.
)";


int pmbc::tileset_command(const std::vector<std::string>& argv)
{
    auto args = docopt::docopt(USAGE, argv);

    auto input_filename = args["<input>"].asString();
    auto output_filename = args["<output>"].asString();
    auto show_info = args["--info"].asBool();

    // ----------------------------------------------------------

    auto f = std::fstream{input_filename};
    if (not f)
    {
        std::printf("ERROR: Failed reading input file: %s\n",
                    input_filename.c_str());
        return -1;
    }
    auto input = json{};

    f >> input;

    auto result = pmbc::read_tiled_tileset(input);
    if (not result.is_valid())
    {
        std::printf("ERROR: %s\n", pmbc::err_to_str(result.error()));
        return -1;
    }

    auto& tiled_tileset = result.value();
    auto tileset_data = pmb::fmt::tileset_data{};

    tileset_data.image       = tiled_tileset.image.c_str();
    tileset_data.columns     = tiled_tileset.columns;
    tileset_data.spacing     = tiled_tileset.spacing;
    tileset_data.tile_height = tiled_tileset.tileheight;
    tileset_data.tile_width  = tiled_tileset.tilewidth;

    if (show_info)
    {
        std::printf("image:       %s\n"
                    "columns:     %i\n"
                    "spacing:     %i\n"
                    "tile_height: %i\n"
                    "tile_width:  %i\n", tileset_data.image,
                                         tileset_data.columns,
                                         tileset_data.spacing,
                                         tileset_data.tile_height,
                                         tileset_data.tile_width);
    }

    std::vector<char> output_buffer;
    output_buffer.resize(1024 * 1024 * 10 /* 10Mib */);

    auto written_span = pmb::fmt::write_tileset(tileset_data, output_buffer);

    if (not written_span.size_bytes())
    {
        std::printf("ERROR: ... :thinking-face: %i %s\n", __LINE__, __FILE__);
        return -1;
    }

    auto output_file = std::fstream{output_filename, std::ios::out |
                                                     std::ios::binary};
    if (not output_file)
    {
        std::printf("ERROR: Failed opening output file: %s\n",
                    output_filename.c_str());
        return -1;
    }

    // FIXME: Check the file was fully written
    output_file.write((const char*) written_span.data(),
                      written_span.size_bytes());

    return 0;
}
