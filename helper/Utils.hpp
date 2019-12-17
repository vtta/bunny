//
//  Utils.hpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

// NOLINTNEXTLINE
#include <glad/glad.h>
// NOLINTNEXTLINE
#include <GLFW/glfw3.h>

#include <cassert>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using usz = size_t;
using uint = unsigned int;

constexpr auto WND_WIDTH = 640;
constexpr auto WND_HEIGHT = 480;

#define ASSERT(x) assert(x)

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

#define CURRENT_DIRECTORY std::filesystem::path(__FILE__).parent_path()

/**
Clear all (unrelated) previous errors.
*/
void GLClearError();

/**
Check for an error and log the error to the console.
@param function The function where the error happend
@param file The file where the error happend
@param line The line number where the error happend
@return Whether there was an error
*/
bool GLLogCall(const char *function, const char *file, int line);

void GLUnbindAll();

inline void GLClearColorBG() {
    GLCall(glClearColor(0.557f, 0.557f, 0.827f, 1.0f));
}

GLFWwindow *GLInit(int width = WND_WIDTH, int height = WND_HEIGHT,
                   const char *title = "OpenGL");

#endif /* Utils_hpp */
