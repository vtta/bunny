//
//  SpinBox.cpp
//  opengl-bunny
//
//  Created by vtta on 12/23/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "SpinBox.hpp"

#include "Utils.hpp"

namespace bunny {
namespace test {

SpinBox::SpinBox(GLFWwindow *wnd) : Test(wnd) {
    glfwSetScrollCallback(
        window_, [](GLFWwindow *window, double xoffset, double yoffset) {
            auto p = reinterpret_cast<WindowUserProperty *>(
                glfwGetWindowUserPointer(window));
            p->camera.moveRight(glm::radians(xoffset / 80.0f * 180.0f));
            p->camera.moveUp(glm::radians(-yoffset / 80.0f * 180.0f));
        });

    std::array positions{
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f,
    };
    std::array indices{
        0U,  1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U, 11U,
        12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U, 21U, 22U, 23U,
        24U, 25U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U,
    };

    vao_ = std::make_unique<VertexArray>();
    vbo_ = std::make_unique<VertexBuffer>(
        positions.data(),
        positions.size() * sizeof(decltype(positions)::value_type));
    VertexBufferLayout layout;
    layout.push<float>(3U);  // point coord
    layout.push<float>(2U);  // texture coord
    vao_->addBuffer(*vbo_, layout);
    ibo_ = std::make_unique<IndexBuffer>(indices.data(), indices.size());
    texture_ = std::make_unique<Texture>(CURRENT_DIRECTORY /
                                         "../res/texture/whu-logo1.png");
    texture_->bind(3);
    shader_ = std::make_unique<Shader>(CURRENT_DIRECTORY /
                                       "../res/shader/SpinBox.shader");
}

SpinBox::~SpinBox() {
    glfwSetScrollCallback(window_, nullptr);
    Test::~Test();
}

void SpinBox::onUpdate(float deltaTime) {
    red_ += step_;
    if (red_ < 0.0f || red_ > 1.0f) {
        step_ *= -1.0f;
    }
}

void SpinBox::onRender() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    shader_->bind();
    for (auto i = 0UL; i < cube_positions_.size(); ++i) {
        auto model = glm::translate(glm::mat4(1.0f), cube_positions_[i]);
        auto angle = 36.0f * i + angle_;
        model = glm::rotate(model, glm::radians(angle),
                            glm::vec3(1.0f, 0.3f, 0.5f));
        auto mvp = proj_ * view_ * model;
        shader_->setUniform4f("u_Color", red_, 0.557f, 0.827f, 1.0f);
        shader_->setUniform1i("u_Texture", 3);
        shader_->setUniformMat4f("u_MVP", mvp);
        renderer_.draw(*vao_, *ibo_, *shader_);
    }
}

void SpinBox::onImGuiRender() {
    ImGui::SameLine();
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);

    ImGui::SliderFloat("Rotate angle", &angle_, 0.0f, 360.0f);
}

}  // namespace test
}  // namespace bunny
