project(inih VERSION 4.9)

add_library(inih STATIC
    ini.c
)
target_include_directories(inih
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
)
