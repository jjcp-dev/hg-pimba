project(stb)

add_library(stb STATIC
    stb_image.c
)
target_include_directories(stb
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
)
