cmake_minimum_required(VERSION 3.28)

project(activity-monitor-agent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)

FetchContent_Declare(
    cpp_httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG        v0.45.0
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(nlohmann_json cpp_httplib)

add_executable(activity-monitor-agent
    src/main.cpp
)

target_link_libraries(activity-monitor-agent PRIVATE
    nlohmann_json::nlohmann_json
    httplib::httplib
)

if (WIN32)
    target_link_libraries(activity-monitor-agent PRIVATE
        kernel32
        user32
    )
endif()
