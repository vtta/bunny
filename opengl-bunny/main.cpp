//
//  main.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

// NOLINTNEXTLINE
#include <glad/glad.h>
// NOLINTNEXTLINE
#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

int main(int argc, const char *argv[]) {
    auto window = GLInit();
    ASSERT(window != nullptr);

    // Ensure we can capture the escape key being pressed below
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    float positions[] = {
        -0.5f, -0.5f,  // 0
        0.5f,  -0.5f,  // 1
        0.5f,  0.5f,   // 2
        -0.5f, 0.5f    // 3
    };

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    // Have to set VAO before binding attrbutes
    VertexArray vao;
    VertexBuffer vbo(positions, 4 * 2 * sizeof(float));

    // define vertex layout
    // This links the attrib pointer wih the buffer at index 0 in the vertex
    // array object
    VertexBufferLayout layout;
    layout.push<float>(2U);
    vao.addBuffer(vbo, layout);

    IndexBuffer ibo(indices, 6);

    Shader shader(CURRENT_DIRECTORY / "../res/shader/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8, 0.3, 0.8, 1.0);

    Renderer render;

    float red = 0.0f;
    float step = 0.01f;
    do {
        // Clear the screen
        render.clear();

        // set shader and set uniform color
        shader.bind();
        shader.setUniform4f("u_Color", red, 0.3, 0.8, 1.0);

        // Draw
        render.draw(vao, ibo, shader);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // increment red
        if (red < 0.0f || red > 1.0f) step *= -1.0;
        red += step;

    }  // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
