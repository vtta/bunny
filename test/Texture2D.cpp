//
//  Texture2D.cpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "Texture2D.hpp"

#include <array>

#include "Utils.hpp"
namespace bunny {
namespace test {

Texture2D::Texture2D() {
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

    vao_ = std::make_unique<VertexArray>();
    vbo_ = std::make_unique<VertexBuffer>(
        positions.data(),
        positions.size() * sizeof(decltype(positions)::value_type));
    VertexBufferLayout layout;
    layout.push<float>(2U);  // point coord
    layout.push<float>(2U);  // texture coord
    vao_->addBuffer(*vbo_, layout);
    ibo_ = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    texture1_ = std::make_unique<Texture>(CURRENT_DIRECTORY /
                                          "../res/texture/whu-logo1.png");
    texture2_ = std::make_unique<Texture>(CURRENT_DIRECTORY /
                                          "../res/texture/whu-logo2.png");
    texture1_->bind(2);
    texture2_->bind(3);

    shader_ = std::make_unique<Shader>(CURRENT_DIRECTORY /
                                       "../res/shader/TestTexture2d.shader");
}

Texture2D::~Texture2D() {}

void Texture2D::onUpdate(float deltaTime) {}

void Texture2D::onRender() {
    // GLClearColorBG();
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    {
        auto model = glm::translate(glm::mat4(1.0f), translationA_);
        auto mvp = proj_ * view_ * model;
        shader_->bind();
        shader_->setUniform4f("u_Color", red_, 0.3, 0.8, 1.0);
        shader_->setUniform1i("u_Texture", 2);
        shader_->setUniformMat4f("u_MVP", mvp);
        renderer_.draw(*vao_, *ibo_, *shader_);
    }

    {
        // draw another one
        auto model = glm::translate(glm::mat4(1.0f), translationB_);
        auto mvp = proj_ * view_ * model;
        shader_->bind();
        shader_->setUniform4f("u_Color", 1.0f - red_, 0.3, 0.8, 1.0);
        shader_->setUniform1i("u_Texture", 3);
        shader_->setUniformMat4f("u_MVP", mvp);
        renderer_.draw(*vao_, *ibo_, *shader_);
    }

    red_ += step_;
    if (red_ < 0.0f || red_ > 1.0f) {
        step_ *= -1.0f;
    }
}

void Texture2D::onImGuiRender() {
    // Edit vec3 using a slider from 0.0f to 1.0f
    ImGui::SliderFloat3("Translation A", &translationA_[0], -WND_HEIGHT,
                        WND_HEIGHT);
    ImGui::SliderFloat3("Translation B", &translationB_[0], -WND_HEIGHT,
                        WND_HEIGHT);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

}  // namespace test
}  // namespace bunny
