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
        auto cos_theta = glm::cos(theta_);
        // if (glm::abs(cos_theta) < 100 * std::numeric_limits<float>::min()) {
        //     return {sgn(cos_theta) * 1.0f, 0.0f, 0.0f};
        // }
        auto vx = glm::vec3(r_ / cos_theta, 0.0f, 0.0f);
        auto vr = glm::vec3(r_ * cos_theta, 0.0f, -r_ * glm::sin(theta_));
        return glm::normalize(vx - vr);
    }
    inline glm::vec3 up() const {
        auto v1 =
            glm::vec3(-r_ * glm::sin(theta_), 0.0f, r_ * glm::cos(theta_));
        auto v2 = position();
        return glm::normalize(glm::cross(v1, v2));
    }

    inline void moveRight(float r) { theta_ -= r; }
    inline void moveUp(float r) { phi_ -= r; }

private:
    float r_{4.0f};
    float theta_{glm::radians(45.0f)};
    float phi_{glm::radians(45.0f)};

    inline float x() const { return r_ * glm::sin(phi_) * glm::cos(theta_); }
    inline float y() const { return r_ * glm::cos(phi_); }
    inline float z() const { return r_ * glm::sin(phi_) * glm::sin(theta_); }
};

}  // namespace bunny

#endif /* Camera_hpp */
