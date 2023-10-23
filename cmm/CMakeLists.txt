project(cmm VERSION 0.0.0)

option(CMM_BUILD_TESTS "Build cmm tests" ON)
option(CMM_BUILD_TOOLS "Build cmm tools" ON)

add_library(cmm STATIC
    src/jb/parser.cpp
    src/jb/writer.cpp
)
target_compile_features(cmm
    PRIVATE
        cxx_std_11
)
target_include_directories(cmm
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(cmm
    PUBLIC
        GSL
)

if (CMM_BUILD_TESTS)
    add_subdirectory(test)
endif ()

if (CMM_BUILD_TOOLS)
    add_subdirectory(tools)
endif ()

