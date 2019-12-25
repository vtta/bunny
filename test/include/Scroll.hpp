//
//  Scroll.hpp
//  opengl-bunny
//
//  Created by vtta on 12/23/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Scroll_hpp
#define Scroll_hpp

#include <array>
#include <memory>

#include "Camera.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Test.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace bunny {
namespace test {

class Scroll : public Test {
public:
    Scroll(GLFWwindow *wnd);
    ~Scroll() override;

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

private:
    float red_{0.0f}, step_{0.01f}, angle_{0.0f};
    Renderer renderer_{};
    std::unique_ptr<VertexArray> vao_;
    std::unique_ptr<VertexBuffer> vbo_;
    std::unique_ptr<IndexBuffer> ibo_;
    std::unique_ptr<Shader> shader_;
    std::unique_ptr<Texture> texture_;

    glm::mat4 proj_{
        glm::perspective(glm::radians(45.0f), 1.0f * WND_WIDTH / WND_HEIGHT,
                         0.1f, 100.0f),
    };
    std::array<glm::vec3, 10> cube_positions_{
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f),
    };

    glm::vec3 camera_direction_{}, camera_up_{};
};

}  // namespace test
}  // namespace bunny

#endif /* Scroll_hpp */
