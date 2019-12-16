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

    std::array positions{
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
    
    // 4x3 aspect ratio
    // left edge, right edge, bottom edge, top edge, near plane, far plane
    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    Shader shader(CURRENT_DIRECTORY / "../res/shader/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8, 0.3, 0.8, 1.0);
    shader.setUniformMat4f("u_MVP", proj);

    Texture texture1(CURRENT_DIRECTORY / "../res/texture/whu-logo1.png");
    Texture texture2(CURRENT_DIRECTORY / "../res/texture/whu-logo2.png");
    texture1.bind(3);
    texture2.bind(5);
    // tell shader which texture slot to use
    shader.setUniform1i("u_Texture", 3);

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

        // increment red
        if (red < 0.0f || red > 1.0f) step *= -1.0;
        red += step;
    } while ((static_cast<void>(glfwSwapBuffers(window)),
              static_cast<void>(glfwPollEvents()), true) &&
             glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
    // Check if the ESC or Q key was pressed or the window was closed

    glfwTerminate();
    return 0;
}
