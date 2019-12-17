//
//  Test.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Test_hpp
#define Test_hpp

namespace test {

class Test {
public:
    Test() {}
    virtual ~Test() {}

    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}
};

}  // namespace test
#endif /* Test_hpp */
