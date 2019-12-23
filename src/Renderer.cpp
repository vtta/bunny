//
//  Renderer.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "Renderer.hpp"
namespace bunny {
void Renderer::draw(const VertexArray &va, const IndexBuffer &ib,
                    const Shader &shader) const {
    shader.bind();
    va.bind();
    ib.bind();

    GLCall(glDrawElements(GL_TRIANGLES, static_cast<int>(ib.count()),
                          GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT););
}
}  // namespace bunny
