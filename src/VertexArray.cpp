//
//  VertexArray.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "VertexArray.hpp"
namespace bunny {
VertexArray::VertexArray() : render_id_(0U) {
    GLCall(glGenVertexArrays(1, &render_id_));
    ASSERT(render_id_ != 0);
}

VertexArray::~VertexArray() {
    unbind();
    GLCall(glDeleteVertexArrays(1, &render_id_));
    render_id_ = 0U;
}

void VertexArray::bind() const { GLCall(glBindVertexArray(render_id_)); }
void VertexArray::unbind() const { GLCall(glBindVertexArray(0)); }

void VertexArray::addBuffer(const VertexBuffer &vb,
                            const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    auto const &elements = layout.elements();
    auto offset = 0U;
    for (u32 i = 0U; i < elements.size(); ++i) {
        auto const &elem = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(
            i, elem.count, elem.type, elem.normalized ? GL_TRUE : GL_FALSE,
            layout.stride(), reinterpret_cast<const void *>(offset)));
        offset += elem.count * VertexBufferElement::sizeOfType(elem.type);
    }
}
}  // namespace bunny
