#include <cstdio>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "docopt.h"

#include "cmm/jb/parser.hpp"


static auto VERSION = "0.0.1";
static auto USAGE = R"(
Prints the contents of a `.jb` file into stdout

  Usage:
    jbdump <input-file>
    jbdump (-h | --help)
    jbdump --version

  Options:
    -h --help     Show this screen.
    --version     Show version.
)";


auto read_file(const char* file_name)
    -> std::vector<char>
{
    std::fstream file(file_name,
                      std::ios::in | std::ios::ate | std::ios::binary);
    auto file_size = file.tellg();
    file.seekg(0);

    std::vector<char> contents;
    contents.resize(file_size);
    file.read(contents.data(), file_size);

    return contents;
}


void indent(int depth)
{
    for (int i = 0; i < depth; i++)
        std::printf(" ");
}

void print(int depth, const cmm::jb::value& v);
void coso(cmm::jb &parser, int depth=0) {
    while (true)
    {
        auto v = parser.next();

        if (v.type() == cmm::jb::type::none)
            break;

        print(depth, v);
    }
}


void print(int depth, const cmm::jb::value& v)
{
    indent(depth);

    switch (v.type()) {
    case cmm::jb::type::i32:
        std::printf("%i <i32>: %i\n", v.id(), v.as_int32());
        break;

    case cmm::jb::type::f32:
        std::printf("%i <f32>: %f\n", v.id(), v.as_float());
        break;

    case cmm::jb::type::str:
        std::printf("%i <str>: %s\n", v.id(), v.as_string());
        break;

    case cmm::jb::type::bin:
        {
            // auto k = cmm::jb{{v.as_binary().data(), v.as_binary().size_bytes()}};
            // coso(k, depth+4);
            // break;
            std::printf("%i <bin>:", v.id());

            auto bin = v.as_binary();
            auto width = 50;

            if (bin.size() == 0)
            {
                std::printf("\n");
                break;
            }

            for (int i = 0; i < v.as_binary().size(); i++)
            {
                if (i % width == 0)
                {
                    std::printf("\n");
                    indent(depth + 4);
                }
                else
                {
                    std::printf(", ");
                }

                std::printf("%02X", (int) bin[i]);
            }
            std::printf("\n");
        }
        break;

    default:
        break;
    }
}


int main(int argc, char *argv[])
{
    auto args = docopt::docopt(USAGE, {argv + 1, argv + argc}, true, VERSION);

    auto& input_file = args["<input-file>"].asString();

    auto contents = read_file(input_file.c_str());

    cmm::jb parser{contents};
    coso(parser, 0);

    return 0;
}
