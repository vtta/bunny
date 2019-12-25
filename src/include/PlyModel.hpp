//
//  PlyModel.hpp
//  opengl-bunny
//
//  Created by vtta on 12/24/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef PlyModel_hpp
#define PlyModel_hpp

#include <fstream>
#include <iostream>
#include <sstream>

#include "Utils.hpp"
#include "Vertex.hpp"

namespace bunny {

class PlyModel {
public:
    PlyModel(std::filesystem::path const &file_path);

    inline u32 *indices() const {
        return reinterpret_cast<u32 *>(indices_.get());
    }
    inline u32 faceNum() const { return f_num_; }
    inline void *vertices() const {
        return reinterpret_cast<void *>(vertices_.get());
    }
    inline u32 vertexNum() const { return v_num_; }

private:
    u32 v_num_{0U}, f_num_{0U};
    std::unique_ptr<Vertex[]> vertices_{nullptr};
    std::unique_ptr<u32[][3]> indices_{nullptr};
    std::filesystem::path file_path_;

    void parse(std::filesystem::path const &file_path);
    void calcVertexNormal();
};

}  // namespace bunny
#endif /* PlyModel_hpp */
