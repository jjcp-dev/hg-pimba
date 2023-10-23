add_executable(lgf_test
    main.cpp
    test_context.cpp
    internal/handle_owner.cpp
    vtx_decl.cpp
    vtx_range.cpp
    vtx_buffer.cpp
)

target_include_directories(lgf_test
    PRIVATE
        SDL2main
        SDL2-static
)

target_link_libraries(lgf_test
    PRIVATE
        Catch2::Catch
        SDL2main
        SDL2-static
        lgf
)

add_test(NAME lgf_test COMMAND lgf_test)
