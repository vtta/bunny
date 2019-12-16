//
//  IndexBuffer.hpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include <glad/glad.h>

#include "Utils.hpp"

class IndexBuffer {
private:
    u32 render_id_;
    // element count
    usz count_;

public:
    IndexBuffer(const u32 *data, usz count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    inline auto count() const { return count_; }
};

#endif /* IndexBuffer_hpp */
