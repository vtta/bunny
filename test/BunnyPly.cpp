//
//  BunnyPly.cpp
//  opengl-bunny
//
//  Created by vtta on 12/24/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "BunnyPly.hpp"

#include "Utils.hpp"

namespace bunny {
namespace test {

BunnyPly::BunnyPly()
    : bunnyModel_(CURRENT_DIRECTORY / "../res/object/bunny.ply") {
    std::array cube_positions{
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
    std::array cube_indices{
        0U,  1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U, 11U,
        12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U, 21U, 22U, 23U,
        24U, 25U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U,
    };

    {
        model_vao_ = std::make_unique<VertexArray>();
        model_vbo_ = std::make_unique<VertexBuffer>(
            bunnyModel_.vertices(), bunnyModel_.vertexNum() * sizeof(Vertex));
        VertexBufferLayout layout;
        layout.push<u32>(1);     // id
        layout.push<float>(3U);  // point coord
        layout.push<float>(2U);  // texture coord
        layout.push<float>(3U);  // normal
        model_vao_->addBuffer(*model_vbo_, layout);
        model_ibo_ = std::make_unique<IndexBuffer>(bunnyModel_.indices(),
                                                   bunnyModel_.faceNum() * 3U);
        model_shader_ = std::make_unique<Shader>(
            CURRENT_DIRECTORY / "../res/shader/BunnyPly.shader");
    }
    {
        light_vao_ = std::make_unique<VertexArray>();
        light_vbo_ = std::make_unique<VertexBuffer>(
            cube_positions.data(), cube_positions.size() * sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(3U);  // point coord
        layout.push<float>(2U);  // texture coord
        layout.push<float>(3U);  // normal
        light_vao_->addBuffer(*light_vbo_, layout);
        light_ibo_ = std::make_unique<IndexBuffer>(cube_indices.data(),
                                                   cube_indices.size());
        light_shader_ = std::make_unique<Shader>(
            CURRENT_DIRECTORY / "../res/shader/BunnyPlyLight.shader");
    }

    texture_ = std::make_unique<Texture>(CURRENT_DIRECTORY /
                                         "../res/texture/whu-logo1.png");
    texture_->bind(3);

    GLCall(glDisable(GL_BLEND));
}

BunnyPly::~BunnyPly() { GLCall(glEnable(GL_BLEND)); }

void BunnyPly::onUpdate(float deltaTime) {
    // std::cout << deltaTime << std::endl;
    red_ += step_;
    if (red_ < 0.0f || red_ > 1.0f) {
        step_ *= -1.0f;
    }
    camera_direction_ = CAMERA.direction();
    camera_up_ = CAMERA.up();
}

void BunnyPly::onRender() {
    // GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    {
        light_shader_->bind();
        auto model = glm::translate(glm::mat4(1.0f), light_pos_);
        model = glm::scale(model, glm::vec3(0.1f));
        auto view = CAMERA.view();
        auto mvp = proj() * view * model;
        light_shader_->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        light_shader_->setUniformMat4f("u_MVP", mvp);
        renderer_.draw(*light_vao_, *light_ibo_, *light_shader_);
    }
    {
        model_shader_->bind();
        model_shader_->setUniform1i("u_Texture", 3);
        auto model = glm::translate(glm::mat4(1.0f), model_positions_[0]);
        model = glm::scale(model, glm::vec3(model_scale_factor_));
        model = glm::rotate(model, glm::radians(angle_), {1.0f, 0.3f, 0.5f});
        auto normMat = glm::transpose(glm::inverse(model));
        model_shader_->setUniform4f("u_ObjectColor", 1.0f, 0.5f, 0.31f, 1.0f);
        model_shader_->setUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);
        model_shader_->setUniform4f("u_LightPos", {light_pos_, 1.0f});
        model_shader_->setUniform4f("u_ViewPos", {CAMERA.position(), 1.0f});
        model_shader_->setUniformMat4f("u_Model", model);
        model_shader_->setUniformMat4f("u_View", CAMERA.view());
        model_shader_->setUniformMat4f("u_Proj", proj());
        model_shader_->setUniformMat4f("u_NormMat", normMat);
        renderer_.draw(*model_vao_, *model_ibo_, *model_shader_);
    }
}

void BunnyPly::onImGuiRender() {
    ImGui::SameLine();
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Rotate angle", &angle_, 0.0f, 360.0f);
    ImGui::SliderFloat("Scale factor", &model_scale_factor_, 0.1f, 16.0f);
    ImGui::SliderFloat("Camera zoom", &zoom_, 0.1f, 80.0f);
    ImGui::SliderFloat3("Camera position", &camera_direction_[0], -4.0f, 4.0f);
    ImGui::SliderFloat3("Camera up", &camera_up_[0], -4.0f, 4.0f);
    ImGui::SliderFloat3("Light position", &light_pos_[0], -4.0f, 4.0f);
    ImGui::SliderFloat3("Model position", &model_positions_[0][0], -4.0f, 4.0f);
}

}  // namespace test
}  // namespace bunny
