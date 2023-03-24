cmake_minimum_required(VERSION 3.24)

include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(ContentSearcher ${HEADERS} ${SOURCES})

target_include_directories(ContentSearcher PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_BINARY_DIR}/include"
        "${PROJECT_BINARY_DIR}"
)

target_link_libraries(ContentSearcher PRIVATE nlohmann_json::nlohmann_json)
