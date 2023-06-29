cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS -pthread)

# clear project with main.cpp for release
project(ContentSearcher VERSION 0.1)
configure_file(VersionConfig.h.in VersionConfig.h)
add_subdirectory(src)

# project with gTest for running tests
project(ContentSearcher_tst)
add_subdirectory(tests)
