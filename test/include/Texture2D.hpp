//
//  Texture2D.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <memory>

#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Test.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
namespace bunny {
namespace test {

class Texture2D : public Test {
public:
    Texture2D(GLFWwindow *wnd);
    ~Texture2D() override;

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

private:
    constexpr static auto divisor = 8.0f;

    glm::vec3 translationA_{-WND_WIDTH / divisor, -WND_HEIGHT / divisor, 0.0f};
    glm::vec3 translationB_{WND_WIDTH / divisor, WND_HEIGHT / divisor, 0.0f};

    std::unique_ptr<VertexArray> vao_;
    std::unique_ptr<VertexBuffer> vbo_;
    std::unique_ptr<IndexBuffer> ibo_;
    std::unique_ptr<Shader> shader_;
    std::unique_ptr<Texture> texture1_;
    std::unique_ptr<Texture> texture2_;

    glm::mat4 proj_ =
        glm::ortho(-WND_WIDTH / 2.0f, WND_WIDTH / 2.0f, -WND_HEIGHT / 2.0f,
                   WND_HEIGHT / 2.0f, -1.0f, 1.0f);
    glm::mat4 view_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    float red_{0.0f}, step_{0.01f};
    Renderer renderer_{};
};

}  // namespace test
}  // namespace bunny
#endif /* Texture2D_hpp */
