//
//  Vertex.hpp
//  opengl-bunny
//
//  Created by vtta on 12/25/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "Utils.hpp"

namespace bunny {

struct Vertex {
    u32 id{0U};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec2 uv{0.0f, 0.0f};
    glm::vec3 normal{0.0f, 0.0f, 0.0f};
};

}  // namespace bunny
#endif /* Vertex_hpp */
