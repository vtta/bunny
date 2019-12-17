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
#include <iostream>

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

    auto divisor = 8.0f;
    std::array positions{
        // bottom left
        -WND_WIDTH / divisor,
        -WND_HEIGHT / divisor,
        0.0f,
        0.0f,
        // bottom right
        WND_WIDTH / divisor,
        -WND_HEIGHT / divisor,
        1.0f,
        0.0f,
        // top right
        WND_WIDTH / divisor,
        WND_HEIGHT / divisor,
        1.0f,
        1.0f,
        // top left
        -WND_WIDTH / divisor,
        WND_HEIGHT / divisor,
        0.0f,
        1.0f,
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

    Texture texture1(CURRENT_DIRECTORY / "../res/texture/whu-logo1.png");
    Texture texture2(CURRENT_DIRECTORY / "../res/texture/whu-logo2.png");
    texture1.bind(3);
    texture2.bind(5);

    Shader shader(CURRENT_DIRECTORY / "../res/shader/basic.shader");
    // shader.bind();
    // shader.setUniform4f("u_Color", 0.8, 0.3, 0.8, 1.0);
    // tell shader which texture slot to use
    // shader.setUniform1i("u_Texture", 3);

    Renderer render;

    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    // 4x3 aspect ratio
    // left edge, right edge, bottom edge, top edge, near plane, far plane
    glm::mat4 proj =
        glm::ortho(-WND_WIDTH / 2.0f, WND_WIDTH / 2.0f, -WND_HEIGHT / 2.0f,
                   WND_HEIGHT / 2.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    auto translationA =
        glm::vec3(-WND_WIDTH / divisor, -WND_HEIGHT / divisor, 0.0f);
    auto translationB =
        glm::vec3(WND_WIDTH / divisor, WND_HEIGHT / divisor, 0.0f);

    auto red = 0.0f, step = 0.01f;
    do {
        // Clear the screen
        render.clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            auto model = glm::translate(glm::mat4(1.0f), translationA);
            auto mvp = proj * view * model;
            shader.bind();
            shader.setUniform4f("u_Color", red, 0.3, 0.8, 1.0);
            shader.setUniform1i("u_Texture", 3);
            shader.setUniformMat4f("u_MVP", mvp);
            render.draw(vao, ibo, shader);
        }

        {
            // draw another one
            auto model = glm::translate(glm::mat4(1.0f), translationB);
            auto mvp = proj * view * model;
            shader.bind();
            shader.setUniform4f("u_Color", 1.0f - red, 0.3, 0.8, 1.0);
            shader.setUniform1i("u_Texture", 5);
            shader.setUniformMat4f("u_MVP", mvp);
            render.draw(vao, ibo, shader);
        }

        // increment red
        red += step;
        if (red < 0.0f || red > 1.0f) {
            step *= -1.0f;
        }

        // Show a simple window that we create ourselves.
        // We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Slider");
            // Edit vec3 using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("Translation A", &translationA[0], -WND_HEIGHT,
                                WND_HEIGHT);
            ImGui::SliderFloat3("Translation B", &translationB[0], -WND_HEIGHT,
                                WND_HEIGHT);
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
