//
//  Renderer.hpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Utils.hpp"
#include "VertexArray.hpp"

class Renderer {
public:
    void draw(const VertexArray &va, const IndexBuffer &ib,
              const Shader &shader) const;
    void clear() const;
};

#endif /* Renderer_hpp */
