cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(libraries/nlohmann_json)


# clear project with main.cpp for release
project(ContentSearcher VERSION 0.1)

configure_file(VersionConfig.h.in VersionConfig.h)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(ContentSearcher ${HEADERS} ${SOURCES})

target_include_directories(ContentSearcher PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include"
        "${PROJECT_BINARY_DIR}")

target_link_libraries(ContentSearcher PRIVATE nlohmann_json::nlohmann_json)


# project with gTest for running tests
project(ContentSearcher_tst)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")
file(GLOB TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_executable(ContentSearcher_tst ${HEADERS} ${SOURCES} ${TESTS})

target_include_directories(ContentSearcher_tst PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include"
        "${PROJECT_BINARY_DIR}"
        )

target_link_libraries(ContentSearcher_tst PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(ContentSearcher_tst PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(ContentSearcher_tst)
