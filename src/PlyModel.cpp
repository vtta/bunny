//
//  PlyModel.cpp
//  opengl-bunny
//
//  Created by vtta on 12/24/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "PlyModel.hpp"

#include <fmt/core.h>

#include <fstream>
#include <glm/gtx/normal.hpp>
#include <iostream>
#include <sstream>

#include "Utils.hpp"

namespace bunny {
PlyModel::PlyModel(std::filesystem::path const &file_path)
    : file_path_(file_path) {
    parse(file_path);
    calcVertexNormal();
}

void PlyModel::calcVertexNormal() {
    // foreach vertex:
    //    set vertex normal to (0,0,0)
    for (auto i = 0U; i < v_num_; ++i) {
        vertices_[i].normal = {0.0f, 0.0f, 0.0f};
    }

    // foreach triangle:
    //    foreach vertex on that triangle:
    //       set vertex normal = normalize( vertex normal + face normal )
    for (auto i = 0U; i < f_num_; ++i) {
        auto const &face = indices_[i];
        auto const &p1 = vertices_[face[0]].position;
        auto const &p2 = vertices_[face[1]].position;
        auto const &p3 = vertices_[face[2]].position;
        auto face_normal = glm::triangleNormal(p3, p2, p1);
        for (auto j = 0U; j < 3; ++j) {
            auto &vertex_normal = vertices_[face[j]].normal;
            vertex_normal = glm::normalize(vertex_normal + face_normal);
        }
    }
}

void PlyModel::parse(std::filesystem::path const &file_path) {
    enum class InputState { HEADER = 0, VERTEX = 1, FACE = 2, END = 3 };

    std::ifstream stream(file_path);
    std::string line, buf;
    u32 v_idx{0U}, f_idx{0U};

    InputState state{InputState::HEADER};

    while (getline(stream, line)) {
        std::stringstream iss{line};
        switch (state) {
            case InputState::HEADER: {
                iss >> buf;
                if (buf == "ply" || buf == "PLY") {
                } else if (buf == "format") {
                } else if (buf == "comment") {
                } else if (buf == "element") {
                    iss >> buf;
                    if (buf == "vertex") {
                        iss >> v_num_;
                        vertices_ =
                            std::unique_ptr<Vertex[]>(new Vertex[v_num_]());
                    } else if (buf == "face") {
                        iss >> f_num_;
                        indices_ =
                            std::unique_ptr<u32[][3]>(new u32[f_num_][3]());
                    } else {
                        ASSERT(false);
                    }
                } else if (buf == "property") {
                } else if (buf == "end_header") {
                    ASSERT(vertices_ != nullptr);
                    ASSERT(indices_ != nullptr);
                    state = InputState::VERTEX;
                } else {
                    ASSERT(false);
                }
                break;
            }
            case InputState::VERTEX: {
                vertices_[v_idx].id = v_idx;
                auto &pos = vertices_[v_idx].position;
                iss >> pos.x;
                iss >> pos.y;
                iss >> pos.z;
                // std::cout << fmt::format("{} {} {}", pos.x, pos.y, pos.z)
                //           << std::endl;
                if (++v_idx >= v_num_) {
                    state = InputState::FACE;
                }
                break;
            }
            case InputState::FACE: {
                auto t = 0U;
                iss >> t;
                if (t == 3U) {
                    auto &f = indices_[f_idx++];
                    iss >> f[0];
                    iss >> f[1];
                    iss >> f[2];
                    // std::cout << fmt::format("{} {} {}", f[0], f[1], f[2])
                    //           << std::endl;
                }
                if (f_idx >= f_num_) {
                    state = InputState::END;
                }
                break;
            }
            case InputState::END:
                break;
            default:
                ASSERT(false);
                break;
        }
    }
    return;
}

}  // namespace bunny
