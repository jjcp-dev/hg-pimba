#include <cstdio>

#include "docopt.h"

#include "./tileset_command.hpp"


static auto VERSION = "0.0.1";
static auto USAGE = R"(
Usage:
    pmbc <command> [<args>...]
    pmbc (-h | --help)
    pmbc --version

Commands:
    tileset       Convert a Tiled JSON tileset.

Options:
    -h --help     Show this screen.
    --version     Show version.
)";


#include <iostream>
int main(int argc, char** argv)
{
    auto args = docopt::docopt(USAGE, {argv + 1, argv + argc}, true, VERSION, true);

    auto command = args["<command>"].asString();

    if (command == "tileset")
        return pmbc::tileset_command(args["<args>"].asStringList());

    return 0;
}
