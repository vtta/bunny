//
//  WindowUserProperty.hpp
//  opengl-bunny
//
//  Created by vtta on 12/25/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef WindowUserProperty_hpp
#define WindowUserProperty_hpp

#include "Camera.hpp"
#include "Utils.hpp"

namespace bunny {

struct WindowUserProperty {
    Camera camera{};
    glm::vec2 lastClicked{};
};

}  // namespace bunny
#endif /* WindowUserProperty_hpp */
