cmake_minimum_required(VERSION 3.0)
project(imgui)
file (GLOB_RECURSE SRC "*.cpp")
add_library(imgui ${SRC})
