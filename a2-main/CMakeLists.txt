cmake_minimum_required(VERSION 3.0)

project(a1)
set(CMAKE_CXX_STANDARD 11)

find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(viewer src/hw.cpp src/viewer.cpp)
target_link_libraries(viewer GLEW::GLEW glm::glm OpenGL::GL SDL2::SDL2)

add_executable(example src/example.cpp)
target_link_libraries(example viewer)

add_executable(part1 src/part1.cpp)
target_link_libraries(part1 viewer)
