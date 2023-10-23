add_executable(cmm_test
    main.cpp
    unused.cpp
    result.cpp
    is_pot.cpp
    buffer.cpp
    byte.cpp
    bit_ops.cpp
    span.cpp
    optional.cpp
    jb/parser.cpp
    jb/writer.cpp
    mem/align.cpp
    mem/linear_allocator.cpp
)
target_compile_features(cmm_test
    PRIVATE
        cxx_std_17
)
target_link_libraries(cmm_test
    PRIVATE
        cmm
        Catch2::Catch
)

add_test(NAME cmm_test COMMAND cmm_test)
