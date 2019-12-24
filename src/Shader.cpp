//
//  Shader.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
namespace bunny {
Shader::Shader(const std::filesystem::path &file_path)
    : render_id_(0U), file_path_(file_path) {
    ShaderProgramSource src = parse(file_path);
    render_id_ = create(src.vertex, src.fragment);
    ASSERT(render_id_ != 0);
}

Shader::~Shader() {
    unbind();
    GLCall(glDeleteProgram(render_id_));
    render_id_ = 0U;
}

void Shader::bind() const { GLCall(glUseProgram(render_id_)); }

void Shader::unbind() const { GLCall(glUseProgram(0)); }

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {
    GLCall(glUniform4f(uniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform4f(const std::string &name, glm::vec4 const &v) {
    GLCall(glUniform4f(uniformLocation(name), v.x, v.y, v.z, v.w));
}

void Shader::setUniform1i(const std::string &name, int value) {
    GLCall(glUniform1i(uniformLocation(name), value));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &mat) {
    GLCall(glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

u32 Shader::uniformLocation(const std::string &name) {
    if (uniform_location_table_.find(name) != uniform_location_table_.end()) {
        return uniform_location_table_[name];
    }
    GLCall(auto location = glGetUniformLocation(render_id_, name.c_str()));
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!"
                  << std::endl;
    }
    uniform_location_table_[name] = location;
    return location;
}

ShaderProgramSource Shader::parse(const std::filesystem::path &file_path) {
    // std::cout << filepath << std::endl;

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::ifstream stream(file_path);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    std::cout << "VERTEX" << std::endl << ss[0].str() << std::endl;
    std::cout << "FRAGMENT" << std::endl << ss[1].str() << std::endl;
    return {ss[0].str(), ss[1].str()};
}

u32 Shader::compile(unsigned int type, const std::string &source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << " shader compile status: " << result << std::endl;
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cerr << "Failed to compile "
                  << (type == GL_VERTEX_SHADER
                          ? "vertex"
                          : (type == GL_FRAGMENT_SHADER ? "fragment"
                                                        : "unknown"))
                  << "shader" << std::endl;
        std::cerr << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

u32 Shader::create(const std::string &vertex_code,
                   const std::string &fragment_code) {
    // create a shader program
    GLCall(u32 program = glCreateProgram());
    ASSERT(program != 0);
    u32 vs = compile(GL_VERTEX_SHADER, vertex_code);
    ASSERT(vs != 0);
    u32 fs = compile(GL_FRAGMENT_SHADER, fragment_code);
    ASSERT(fs != 0);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));

    GLint program_linked;

    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
        std::cerr << "Failed to link program" << std::endl;
        std::cerr << message << std::endl;
    }

    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
}  // namespace bunny
