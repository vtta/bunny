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

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

int main(int argc, const char *argv[]) {
    auto window = GLInit();
    ASSERT(window != nullptr);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::array positions = {
        -0.5f, -0.5f, 0.0f, 0.0f,  // 0 bottom left
        0.5f,  -0.5f, 1.0f, 0.0f,  // 1 bottom right
        0.5f,  0.5f,  1.0f, 1.0f,  // 2 top right
        -0.5f, 0.5f,  0.0f, 1.0f,  // 3 top left
    };
    std::array indices{0U, 1U, 2U, 2U, 3U, 0U};

    // Have to set VAO before binding attrbutes
    VertexArray vao;
    VertexBuffer vbo(positions.data(), sizeof(decltype(positions)::value_type) *
                                           positions.size());

    // define vertex layout
    // This links the attrib pointer wih the buffer at index 0 in the vertex
    // array object
    VertexBufferLayout layout;
    // point coord
    layout.push<float>(2U);
    // texture coord
    layout.push<float>(2U);
    vao.addBuffer(vbo, layout);

    IndexBuffer ibo(indices.data(), indices.size());

    Shader shader(CURRENT_DIRECTORY / "../res/shader/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8, 0.3, 0.8, 1.0);

    Texture texture(CURRENT_DIRECTORY / "../res/texture/whu-logo1.png");
    texture.bind(0);
    shader.setUniform1i("u_Texture", 0);

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
