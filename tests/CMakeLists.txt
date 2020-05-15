cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)

project(tests)

set(src main.cpp)

add_executable(test ${src})
target_link_libraries(test lokimath)
