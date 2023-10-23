project(lgf)

add_library(lgf STATIC
    # src/gl/systems.cpp
    # src/gl/texture.cpp
    # src/gl/vtx_buffer.cpp
    # src/gl/idx_buffer.cpp
    # src/gl/program.cpp
    # src/gl/shader.cpp
    # src/gl/systems.cpp
    # src/gl/lgf.cpp
    # src/gl/device.cpp
    # src/gl/render_list.cpp
    src/log.cpp
    src/opengl/lgf.cpp
    src/opengl/opengl.cpp
    src/opengl/backends.cpp
    src/opengl/vtx_buffer.cpp
    src/opengl/command_list.cpp
    src/opengl/texture.cpp
    src/opengl/shader.cpp
)
target_include_directories(lgf
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(lgf
    PUBLIC
        glm
        cmm
        glad
)

add_subdirectory(test)
