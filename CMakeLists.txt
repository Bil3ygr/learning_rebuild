cmake_minimum_required(VERSION 3.0.0)
project(learning VERSION 0.1.0)

include_directories(include)
link_directories(lib)

file(GLOB_RECURSE sources src/*.cpp src/*.h)

add_executable(learning ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
