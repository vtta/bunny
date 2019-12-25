//
//  ClearColor.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef ClearColor_hpp
#define ClearColor_hpp

#include <array>

#include "Test.hpp"
namespace bunny {
namespace test {

class ClearColor : public Test {
public:
    ClearColor(GLFWwindow *wnd) : Test(wnd) {}
    ~ClearColor() override {}

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

private:
    std::array<float, 4> color_{0.557f, 0.557f, 0.827f, 1.0f};
};

}  // namespace test
}  // namespace bunny
#endif /* ClearColor_hpp */
