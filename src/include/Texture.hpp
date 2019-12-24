//
//  Texture.hpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <filesystem>

#include "Utils.hpp"
namespace bunny {
class Texture {
private:
    u32 render_id_{0};
    std::filesystem::path file_path_;
    int width_{0}, height_{0};
    // bits per pixel
    int bpp_{0};
    u8 *local_buffer_{nullptr};

public:
    Texture(const std::filesystem::path &file_path);
    ~Texture();
    void bind(u32 slot = 0U) const;
    void unbind() const;

    inline auto width() const { return width_; }
    inline auto height() const { return height_; }
};
}  // namespace bunny
#endif /* Texture_hpp */
