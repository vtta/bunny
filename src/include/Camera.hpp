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
    Camera() = default;
    ~Camera() = default;
    Camera(float r, float theta, float phi) : r_(r), theta_(theta), phi_(phi) {}

    inline glm::vec3 position() const { return {x(), y(), z()}; }
    inline glm::vec3 direction() const { return {-x(), -y(), -z()}; }
    inline glm::vec3 right() const {
        glm::vec3 y{0.0f, 1.0f, 0.0f}, r{x(), 0.0f, z()};
        return glm::normalize(glm::cross(y, r));
    }
    inline glm::vec3 up() const {
        glm::vec3 v{-r_ * glm::sin(theta_), 0.0f, r_ * glm::cos(theta_)};
        return glm::normalize(glm::cross(v, position()));
    }

    inline glm::mat4 view() const {
        return glm::lookAt(position(), glm::vec3(0.0f), up());
    }

    inline void moveRight(float r) { theta_ -= r; }
    inline void moveUp(float r) { phi_ -= r; }

private:
    float r_{6.0f};
    float theta_{glm::radians(45.0f)};
    float phi_{glm::radians(45.0f)};

    inline float x() const { return r_ * glm::sin(phi_) * glm::cos(theta_); }
    inline float y() const { return r_ * glm::cos(phi_); }
    inline float z() const { return r_ * glm::sin(phi_) * glm::sin(theta_); }
};

}  // namespace bunny

#endif /* Camera_hpp */
