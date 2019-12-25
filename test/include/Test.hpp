//
//  Test.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Test_hpp
#define Test_hpp

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Camera.hpp"
#include "Utils.hpp"
#include "WindowUserProperty.hpp"

namespace bunny {
namespace test {

class Test {
public:
    Test() = delete;
    Test(GLFWwindow *wnd) : window_(wnd) {
        glfwSetWindowUserPointer(window_, new WindowUserProperty());
        auto p = reinterpret_cast<WindowUserProperty *>(
            glfwGetWindowUserPointer(window_));
        if (p) {
            camera_ = &p->camera;
        }
    }
    virtual ~Test() {
        delete reinterpret_cast<WindowUserProperty *>(
            glfwGetWindowUserPointer(window_));
        glfwSetWindowUserPointer(window_, nullptr);
    }

    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}

protected:
    GLFWwindow *window_{nullptr};
    Camera *camera_{nullptr};
};

class TestMenu : public Test {
public:
    TestMenu(GLFWwindow *wnd, std::shared_ptr<Test> &current);
    ~TestMenu() override;

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

    template <typename T>
    void registerTest(const std::string &name) {
        std::cout << "Registering test " << name << std::endl;
        tests_[name] = [](GLFWwindow *wnd) { return std::make_shared<T>(wnd); };
    }

private:
    // store the name of test and corresponding creator
    std::unordered_map<std::string,
                       std::function<std::shared_ptr<Test>(GLFWwindow *wnd)>>
        tests_;
    std::shared_ptr<Test> &current_;
};

}  // namespace test
}  // namespace bunny
#endif /* Test_hpp */
