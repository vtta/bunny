//
//  VertexBufferLayout.hpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <vector>

#include "Utils.hpp"

struct VertexBufferElement {
    u32 type;
    u32 count;
    bool normalized;

    static u32 sizeOfType(u32 type) {
        switch (type) {
            case GL_FLOAT:
                return 4U;
            case GL_UNSIGNED_INT:
                return 4U;
            case GL_UNSIGNED_BYTE:
                return 1U;
            default:
                ASSERT(false);
        }
        return 0U;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements_;
    u32 stride_{0U};

public:
    VertexBufferLayout() = default;
    ~VertexBufferLayout() = default;

    template <typename T>
    void push(u32 count) {
        ASSERT(false);
    }

    template <>
    void push<float>(u32 count) {
        elements_.push_back({GL_FLOAT, count, false});
        stride_ += count * VertexBufferElement::sizeOfType(GL_FLOAT);
    }

    template <>
    void push<u32>(u32 count) {
        elements_.push_back({GL_UNSIGNED_INT, count, false});
        stride_ += count * VertexBufferElement::sizeOfType(GL_UNSIGNED_INT);
    }

    template <>
    void push<u8>(u32 count) {
        elements_.push_back({GL_UNSIGNED_BYTE, count, false});
        stride_ += count * VertexBufferElement::sizeOfType(GL_UNSIGNED_BYTE);
    }

    inline u32 stride() const { return stride_; }

    inline auto const &elements() const { return elements_; }
};

#endif /* VertexBufferLayout_hpp */
