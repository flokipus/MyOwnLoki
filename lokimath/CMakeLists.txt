cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)

project(lokimath)

#set(src inc/lokialg/mean.h)

add_library(lokimath INTERFACE)
target_include_directories(lokimath INTERFACE inc/)
