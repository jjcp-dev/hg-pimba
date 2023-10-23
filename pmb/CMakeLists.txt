project(pmb)

option(PMB_BUILD_TESTS "Build test suit" ON)
option(PMB_BUILD_TOOLS "Build CLI tools" ON)

add_library(pmb STATIC
    ./src/parsers/sprite_parser.cpp
    ./src/parsers/sprite_sheet_parser.cpp

    ./src/2d/sprite_batcher.cpp

    ./src/engine.cpp
    ./src/shader_store.cpp
    ./src/resource.cpp

    ./src/anim/clip.cpp

    ./src/formats/tileset.cpp
)

target_compile_features(pmb
    PUBLIC
        cxx_std_11
)
target_include_directories(pmb
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(pmb
    PUBLIC
        cmm
        lgf
        stb
    PRIVATE
        inih
)

if (PMB_BUILD_TOOLS)
    add_subdirectory(tools)
endif()

if (PMB_BUILD_TESTS)
    add_subdirectory(test)
endif()
