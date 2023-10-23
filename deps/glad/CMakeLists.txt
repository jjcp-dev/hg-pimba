project(glad)

add_library(glad STATIC
    ${PROJECT_SOURCE_DIR}/src/glad.c
)

target_include_directories(glad
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(glad
    PUBLIC
        dl
)
