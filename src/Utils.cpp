//
//  Utils.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "Utils.hpp"

#include <iostream>

#include "Camera.hpp"

namespace bunny {

Camera CAMERA;

GLFWwindow *GLInit(int width, int height, const char *title) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    // --------------------
    auto *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);
    glfwSetScrollCallback(
        window, [](GLFWwindow *window, double xoffset, double yoffset) {
            CAMERA.moveRight(glm::radians(xoffset / 80.0f * 180.0f));
            CAMERA.moveUp(glm::radians(-yoffset / 80.0f * 180.0f));
        });

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // configure global opengl state
    // -----------------------------
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // GLCall(glEnable(GL_POLYGON_OFFSET_FILL));
    // GLCall(glPolygonOffset(-1.0f, -1.0f));

    // Light purple background
    GLClearColorBG();

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;
    return window;
}

void GLClearError() {
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char *function, const char *file, int line) {
    bool noError = true;
    while (GLenum error = glGetError() != GL_NO_ERROR) {
        std::cerr << "[OpenGL Error] (" << std::hex << error << ") in "
                  << function << " at " << file << " on line " << std::dec
                  << line << std::endl;
        noError = false;
    }
    return noError;
}

void GLUnbindAll() {
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}

}  // namespace bunny
