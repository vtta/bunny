//
//  main.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include <glad/glad.h>
// NOLINT
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
#include "imgui.h"
// NOLINT
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(int argc, const char *argv[]) {
    auto window = GLInit();
    ASSERT(window != nullptr);

    std::array positions{
        200.0f, 120.0f, 0.0f, 0.0f,  // 0 bottom left
        440.0f, 120.0f, 1.0f, 0.0f,  // 1 bottom right
        440.0f, 360.0f, 1.0f, 1.0f,  // 2 top right
        200.0f, 360.0f, 0.0f, 1.0f,  // 3 top left
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
    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    // move everything to the left (the same as moving camera to the right)
    // move everything down (the same as moving camera up)
    glm::mat4 view =
        glm::translate(glm::mat4(1.0f), glm::vec3(-200.f, -120.0f, 0.0f));

    Shader shader(CURRENT_DIRECTORY / "../res/shader/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8, 0.3, 0.8, 1.0);

    Texture texture1(CURRENT_DIRECTORY / "../res/texture/whu-logo1.png");
    Texture texture2(CURRENT_DIRECTORY / "../res/texture/whu-logo2.png");
    texture1.bind(3);
    texture2.bind(5);
    // tell shader which texture slot to use
    shader.setUniform1i("u_Texture", 3);

    Renderer render;
    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    // Our state
    float red = 0.0f;
    float step = 0.01f;
    auto translation = glm::vec3(100.0f, 60.0f, 0.0f);

    do {
        // Clear the screen
        render.clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // move the object in the oppsite direction
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        auto mvp = proj * view * model;

        // set shader and set uniform color
        shader.bind();
        shader.setUniform4f("u_Color", red, 0.3, 0.8, 1.0);
        shader.setUniformMat4f("u_MVP", mvp);

        // Draw
        render.draw(vao, ibo, shader);

        // increment red
        if (red < 0.0f || red > 1.0f) step *= -1.0;
        red += step;

        // Show a simple window that we create ourselves.
        // We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Slider");
            // Edit vec3 using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("Translation", &translation[0], 0.0f, 640.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    } while ((static_cast<void>(glfwSwapBuffers(window)),
              static_cast<void>(glfwPollEvents()), true) &&
             glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
    // Check if the ESC or Q key was pressed or the window was closed

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
