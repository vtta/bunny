//
//  ObjReader.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef ObjReader_hpp
#define ObjReader_hpp

#include <map>
#include <vector>

#include "Utils.hpp"
namespace bunny {
class ObjReader {
public:
    ObjReader(std::filesystem::path file_path);

    inline const std::vector<glm::vec3> &v() const { return *v_; }
    inline const std::vector<glm::vec2> &vt() const { return *vt_; }
    inline const std::vector<glm::vec3> &vn() const { return *vn_; }
    inline const std::vector<glm::uvec3> &f() const { return *f_; }

private:
    // index starting from 1, need to fill index 0 with dummy value
    std::unique_ptr<std::vector<glm::vec3>> v_{nullptr};
    std::unique_ptr<std::vector<glm::vec2>> vt_{nullptr};
    std::unique_ptr<std::vector<glm::vec3>> vn_{nullptr};
    // f 8/11/7 7/12/7 6/10/7
    // corrensponding index
    // vertex   8  7 12
    // texture 11 12 10
    // normal   7  7  7
    std::unique_ptr<std::vector<glm::uvec3>> f_{nullptr};
};
}  // namespace bunny
#endif /* ObjReader_hpp */
