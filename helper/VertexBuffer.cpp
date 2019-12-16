//
//  VertexBuffer.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void *data, usz size) {
    GLCall(glGenBuffers(1, &render_id_));
    ASSERT(render_id_ != 0U);
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, render_id_));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { GLCall(glDeleteBuffers(1, &render_id_)); }

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, render_id_));
}

void VertexBuffer::unbind() const { GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
