cmake_minimum_required(VERSION 3.0)
project(stb_image)
file (GLOB_RECURSE SRC "*.c")
add_library(stb_image ${SRC})
