//
//  VertexBuffer.hpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <glad/glad.h>

#include "Utils.hpp"
namespace bunny {
class VertexBuffer {
private:
    u32 render_id_;

public:
    VertexBuffer(const void *data, usz size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};
}  // namespace bunny
#endif /* VertexBuffer_hpp */
