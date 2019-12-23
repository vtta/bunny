//
//  IndexBuffer.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "IndexBuffer.hpp"
namespace bunny {
IndexBuffer::IndexBuffer(const u32 *data, usz count) : count_(count) {
    ASSERT(sizeof(u32) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &render_id_));
    ASSERT(render_id_ != 0U);
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id_));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * this->count(),
                        data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { GLCall(glDeleteBuffers(1, &render_id_)); }

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id_));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U));
}
}  // namespace bunny
