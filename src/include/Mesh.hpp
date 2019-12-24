//
//  Mesh.hpp
//  opengl-bunny
//
//  Created by vtta on 12/20/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <array>
#include <forward_list>
#include <vector>

#include "Utils.hpp"
namespace bunny {
class Mesh {
private:
    std::unique_ptr<std::vector<std::array<float, 3>>> vertices;
    std::unique_ptr<std::vector<std::forward_list<u32>>> faces;
    std::unique_ptr<std::vector<std::array<u32, 3>>> indices;
};
}  // namespace bunny
#endif /* Mesh_hpp */
