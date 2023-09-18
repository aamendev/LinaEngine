cmake_minimum_required(VERSION 3.17)

project(main)
FILE(GLOB SRC
    "../Math/*.h"
    "../Math/*.hpp"
    "../Math/src/*.cpp"
    "../Graphics/*.h"
    "../Graphics/src/*.c"
    "../Graphics/src/*.cpp"
    "../Events/*.h"
    ".h"
    "*.cpp"
    )
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} GL dl glfw)
