cmake_minimum_required(VERSION 3.5)
project(Pimba)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

add_subdirectory(deps)
add_subdirectory(cmm)
add_subdirectory(lgf)
add_subdirectory(pimba)
add_subdirectory(pmb)
