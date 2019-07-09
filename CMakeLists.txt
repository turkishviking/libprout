cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(libprout)

option(BUILD_TESTING "Create tests using CMake" TRUE)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        "include/"
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        stdc++fs
        pthread
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
