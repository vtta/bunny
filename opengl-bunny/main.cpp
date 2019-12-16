//
//  main.cpp
//  opengl-bunny
//
//  Created by vtta on 12/16/19.
//  Copyright © 2019 vtta. All rights reserved.
//

// NOLINTNEXTLINE
#include <glad/glad.h>
// NOLINTNEXTLINE
#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static struct ShaderProgramSource ParseShader(const std::string &filepath) {
    // std::cout << filepath << std::endl;

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::ifstream stream(filepath);
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

    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type,
                                  const std::string &source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    std::cerr << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
              << " shader compile status: " << result << std::endl;
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cerr << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << "shader" << std::endl;
        std::cerr << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader,
                                 const std::string &fragmentShader) {
    // create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));

    GLint program_linked;

    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
    std::cerr << "Program link status: " << program_linked << std::endl;
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

int main(int argc, const char *argv[]) {
    auto window = GLInit();
    ASSERT(window != nullptr);

    // Ensure we can capture the escape key being pressed below
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    float positions[] = {
        -0.5f, -0.5f,  // 0
        0.5f,  -0.5f,  // 1
        0.5f,  0.5f,   // 2
        -0.5f, 0.5f    // 3
    };

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    // Have to set VAO before binding attrbutes
    VertexArray vao;
    VertexBuffer vbo(positions, 4 * 2 * sizeof(float));

    // define vertex layout
    // This links the attrib pointer wih the buffer at index 0 in the vertex
    // array object
    VertexBufferLayout layout;
    layout.push<float>(2U);
    vao.addBuffer(vbo, layout);

    IndexBuffer ibo(indices, 6);

    ShaderProgramSource source =
        ParseShader(CURRENT_DIRECTORY / "../res/shader/basic.shader");

    // std::cout << "VERTEX" << std::endl << source.VertexSource << std::endl;
    // std::cout << "FRAGMENT" << std::endl << source.FragmentSource <<
    // std::endl;

    unsigned int shader =
        CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    GLCall(unsigned int u_Color = glGetUniformLocation(shader, "u_Color"));
    ASSERT(u_Color != -1);

    float red = 0.0f;
    float step = 0.05f;

    do {
        // Clear the screen
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT););

        // set shader and set uniform color
        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(u_Color, red, 0.3, 0.8, 1.0));

        // Instead of binding vertex buffer, attrib pointer, just bind
        // Vertex Array Object
        vao.bind();

        // Bind index buffer
        ibo.bind();

        // Draw
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // increment red
        if (red < 0.0f || red > 1.0f) step *= -1.0;
        red += step;

    }  // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Cleanup VBO
    GLCall(glDeleteProgram(shader));

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
