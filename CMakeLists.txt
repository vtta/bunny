cmake_minimum_required(VERSION 3.15)
project(bunny)

set(CMAKE_CXX_STANDARD 20)

add_executable(bunny main.cpp)

include_directories (include)
include_directories (test/include)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(bunny src_static test_static)

add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)
target_link_libraries(bunny glfw ${GLFW_LIBRARIES})
# target_link_libraries(bunny glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

add_subdirectory(vendor/glad)
include_directories (vendor/glad/include)
target_link_libraries(bunny glad)

include_directories (vendor/glm)

add_subdirectory(vendor/fmt)
include_directories (vendor/fmt/include)
target_link_libraries(bunny fmt)


