//
//  LightingColor.cpp
//  opengl-bunny
//
//  Created by vtta on 12/24/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "LightingColor.hpp"

#include "Utils.hpp"

namespace bunny {
namespace test {

LightingColor::LightingColor(GLFWwindow *wnd) : Test(wnd) {
    glfwSetScrollCallback(
        window_, [](GLFWwindow *window, double xoffset, double yoffset) {
            auto p = reinterpret_cast<WindowUserProperty *>(
                glfwGetWindowUserPointer(window));
            p->camera.moveRight(glm::radians(xoffset / 80.0f * 180.0f));
            p->camera.moveUp(glm::radians(-yoffset / 80.0f * 180.0f));
        });

    std::array positions{
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f,
        -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 1.0f,
        1.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  0.0f,
        0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f, -0.5f, -0.5f,
        0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
        0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f,
        0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  1.0f,
        0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 1.0f,  1.0f,  -1.0f,
        0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f,
        0.5f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1.0f,
        0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
        -0.5f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  -1.0f, 0.0f,
        0.5f,  -0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f,
        0.5f,  1.0f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
        0.0f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,
        -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  -1.0f, 0.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
        -0.5f, 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,
        0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    };
    std::array indices{
        0U,  1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U, 11U,
        12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U, 21U, 22U, 23U,
        24U, 25U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U,
    };

    cube_vao_ = std::make_unique<VertexArray>();
    light_vao_ = std::make_unique<VertexArray>();
    vbo_ = std::make_unique<VertexBuffer>(
        positions.data(),
        positions.size() * sizeof(decltype(positions)::value_type));
    VertexBufferLayout layout;
    layout.push<float>(3U);  // point coord
    layout.push<float>(2U);  // texture coord
    layout.push<float>(3U);  // normal
    cube_vao_->addBuffer(*vbo_, layout);
    light_vao_->addBuffer(*vbo_, layout);
    ibo_ = std::make_unique<IndexBuffer>(indices.data(), indices.size());
    texture_ = std::make_unique<Texture>(CURRENT_DIRECTORY /
                                         "../res/texture/whu-logo1.png");
    texture_->bind(3);
    cube_shader_ = std::make_unique<Shader>(
        CURRENT_DIRECTORY / "../res/shader/LightingColor.shader");
    light_shader_ = std::make_unique<Shader>(
        CURRENT_DIRECTORY / "../res/shader/LightingColorLight.shader");

    GLCall(glDisable(GL_BLEND));
}

LightingColor::~LightingColor() {
    GLCall(glEnable(GL_BLEND));
    glfwSetScrollCallback(window_, nullptr);
    Test::~Test();
}

void LightingColor::onUpdate(float deltaTime) {
    // std::cout << deltaTime << std::endl;
    red_ += step_;
    if (red_ < 0.0f || red_ > 1.0f) {
        step_ *= -1.0f;
    }
    camera_direction_ = camera_->direction();
    camera_up_ = camera_->up();
}

void LightingColor::onRender() {
    glm::vec3 lightPos{1.2f, 1.0f, 2.0f};
    // GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    {
        light_shader_->bind();
        auto model = glm::translate(glm::mat4(1.0f), lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        auto view = camera_->view();
        auto mvp = proj() * view * model;
        light_shader_->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        light_shader_->setUniformMat4f("u_MVP", mvp);
        renderer_.draw(*light_vao_, *ibo_, *light_shader_);
    }
    {
        cube_shader_->bind();
        cube_shader_->setUniform1i("u_Texture", 3);
        auto model = glm::translate(glm::mat4(1.0f), cube_positions_[0]);
        model = glm::rotate(model, glm::radians(angle_), {1.0f, 0.3f, 0.5f});
        auto normMat = glm::transpose(glm::inverse(model));
        cube_shader_->setUniform4f("u_ObjectColor", 1.0f, 0.5f, 0.31f, 1.0f);
        cube_shader_->setUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);
        cube_shader_->setUniform4f("u_LightPos", {lightPos, 1.0f});
        cube_shader_->setUniform4f("u_ViewPos", {camera_->position(), 1.0f});
        cube_shader_->setUniformMat4f("u_Model", model);
        cube_shader_->setUniformMat4f("u_View", camera_->view());
        cube_shader_->setUniformMat4f("u_Proj", proj());
        cube_shader_->setUniformMat4f("u_NormMat", normMat);
        renderer_.draw(*cube_vao_, *ibo_, *cube_shader_);
    }
}

void LightingColor::onImGuiRender() {
    ImGui::SameLine();
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Rotate angle", &angle_, 0.0f, 360.0f);
    ImGui::SliderFloat("Camera zoom", &zoom_, 0.1f, 80.0f);
    ImGui::SliderFloat3("Camera position", &camera_direction_[0], -4.0f, 4.0f);
    ImGui::SliderFloat3("Camera up", &camera_up_[0], -4.0f, 4.0f);
}

}  // namespace test
}  // namespace bunny
