cmake_minimum_required(VERSION 3.24)
project(ContentSearcher VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(libraries/nlohmann_json)

configure_file(VersionConfig.h.in VersionConfig.h)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(ContentSearcher ${HEADERS} ${SOURCES})

target_include_directories(ContentSearcher PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include"
        "${PROJECT_BINARY_DIR}")

target_link_libraries(ContentSearcher PRIVATE nlohmann_json::nlohmann_json)
