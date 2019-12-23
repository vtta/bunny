//
//  Test.cpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "Test.hpp"

#include "Utils.hpp"
namespace bunny {
namespace test {

TestMenu::TestMenu(std::shared_ptr<Test> &current) : current_(current) {
    // GLUnbindAll();
}

TestMenu::~TestMenu() {}

void TestMenu::onUpdate(float deltaTime) {}

void TestMenu::onRender() {}

void TestMenu::onImGuiRender() {
    for (auto const &test : tests_) {
        if (ImGui::Button(test.first.c_str())) {
            // call the test creator and point current test (it's a reference)
            // to it
            current_ = test.second();
        }
    }
}

}  // namespace test
}  // namespace bunny
