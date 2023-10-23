add_executable(pmb_test
    ./main.cpp

    ./2d/rect.cpp
    ./2d/sprite.cpp
    ./2d/sprite_batcher_writer.cpp

    ./parsers/sprite_parser.cpp

    ./anim/cursor.cpp
    ./anim/clip.cpp
)
target_link_libraries(pmb_test
    PRIVATE
        Catch2::Catch
        pmb
)
add_test(NAME pmb_test COMMAND pmb_test)
