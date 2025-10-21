cmake_minimum_required(VERSION 3.5)
project(wixed)

set(CMAKE_CXX_STANDARD 20)
# Adding lib as include dir for sources
include_directories(lib)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
