//
//  Camera.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <limits>

#include "Utils.hpp"

namespace bunny {

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class Camera {
public:
    float r{2.0f};
    float theta{glm::radians(45.0f)};
    float phi{glm::radians(45.0f)};

    Camera() = default;
    ~Camera() = default;
    Camera(float r, float theta, float phi) : r(r), theta(theta), phi(phi) {}

    inline glm::vec3 position() const { return {x(), y(), z()}; }
    inline glm::vec3 direction() const { return {-x(), -y(), -z()}; }
    inline glm::vec3 right() const {
        glm::vec3 y{0.0f, 1.0f, 0.0f}, r{x(), 0.0f, z()};
        return glm::normalize(glm::cross(y, r));
    }
    inline glm::vec3 up() const {
        glm::vec3 v{-r * glm::sin(theta), 0.0f, r * glm::cos(theta)};
        return glm::normalize(glm::cross(v, position()));
    }

    inline glm::mat4 view() const {
        return glm::lookAt(position(), glm::vec3(0.0f), up());
    }

    inline void moveRight(float rad) { theta -= rad; }
    inline void moveUp(float rad) { phi -= rad; }

    inline float x() const { return r * glm::sin(phi) * glm::cos(theta); }
    inline float y() const { return r * glm::cos(phi); }
    inline float z() const { return r * glm::sin(phi) * glm::sin(theta); }
};

}  // namespace bunny

#endif /* Camera_hpp */
