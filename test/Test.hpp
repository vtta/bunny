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
#include <map>
#include <memory>

namespace test {

class Test {
public:
    Test() {}
    virtual ~Test() {}

    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}
};

class TestMenu : public Test {
public:
    TestMenu(std::shared_ptr<Test> &current);
    ~TestMenu();

    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;

    template <typename T>
    void registerTest(const std::string &name) {
        std::cout << "Registering test " << name << std::endl;
        tests_[name] = []() { return std::make_shared<T>(); };
    }

private:
    // store the name of test and corresponding creator
    std::map<std::string, std::function<std::shared_ptr<Test>()>> tests_;
    std::shared_ptr<Test> &current_;
};

}  // namespace test
#endif /* Test_hpp */
