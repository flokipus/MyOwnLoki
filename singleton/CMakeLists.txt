cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)

project(myownsingleton)

set(src inc/Singleton.h)

add_library(singleton_loki INTERFACE)
target_include_directories(singleton_loki INTERFACE inc/)
