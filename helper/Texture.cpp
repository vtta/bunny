//
//  Texture.cpp
//  opengl-bunny
//
//  Created by vtta on 12/17/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "Texture.hpp"

#include "stb_image.h"

Texture::Texture(const std::filesystem::path &file_path)
    : file_path_(file_path) {
    // OpenGL's origin starts from bottom left !! for PNG only
    stbi_set_flip_vertically_on_load(1);
    local_buffer_ = stbi_load(file_path.c_str(), &width_, &height_, &bpp_, 4);
    ASSERT(local_buffer_ != nullptr);

    GLCall(glGenTextures(1, &render_id_));
    ASSERT(render_id_ != 0);
    GLCall(glBindTexture(GL_TEXTURE_2D, render_id_));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // horizontal wrap, clamp, not extend ther area
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width(), height(), 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    if (local_buffer_) {
        stbi_image_free(local_buffer_);
    }
}

Texture::~Texture() { GLCall(glDeleteTextures(1, &render_id_)); }

void Texture::bind(u32 slot) const {
    // select which tecxture slot to bind
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, render_id_));
}

void Texture::unbind() const { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); }
