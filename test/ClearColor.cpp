//
//  ClearColor.cpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "ClearColor.hpp"

#include "Utils.hpp"
namespace bunny {
namespace test {

void ClearColor::onUpdate(float deltaTime) {}

void ClearColor::onRender() {
    GLCall(glClearColor(color_[0], color_[1], color_[2], color_[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT););
}

void ClearColor::onImGuiRender() {
    ImGui::ColorEdit4("Clear Color", color_.data());
}

}  // namespace test
}  // namespace bunny
