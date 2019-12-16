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

GLFWwindow *GLInit(int width = 800, int height = 600,
                   const char *title = "OpenGL");

#endif /* Utils_hpp */
