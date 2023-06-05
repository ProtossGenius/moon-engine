#include "Shader.h"
#include "GL/glew.h"
#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace oogl {
Shader::Shader(const std::string filepath)
    : m_RendererID(0)
    , m_FilePath(filepath) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FregmentSource);
}

Shader::~Shader() { GLCall(glDeleteProgram(m_RendererID)); }

void Shader::Bind() const { GLCall(glUseProgram(m_RendererID)); }

void Shader::Unbind() const { GLCall(glUseProgram(0)); }

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,
                              &matrix[ 0 ][ 0 ]));
}

void Shader::SetUniform1f(const std::string &name, float value) {
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string &name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

ShaderProgramSource Shader::ParseShader(const std::string &filePath) {
    std::fstream stream(filePath);
    std::string  line;
    enum class ShaderType {
        NONE     = -1,
        VERTEX   = 0,
        FREGMENT = 1,
    };
    ShaderType        type = ShaderType::NONE;
    std::stringstream ss[ 2 ];
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fregment") != std::string::npos) {
                type = ShaderType::FREGMENT;
            }
        } else {
            ss[ int(type) ] << line << "\n";
        }
    }
    return {ss[ 0 ].str(), ss[ 1 ].str()};
}

unsigned int Shader::CompileShader(unsigned int       type,
                                   const std::string &source) {
    unsigned int id  = glCreateShader(type);
    const char  *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (GL_FALSE == result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fregment")
                  << " shader !" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader,
                                  const std::string &fregmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs      = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs      = CompileShader(GL_FRAGMENT_SHADER, fregmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return program;
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[ name ];
    }
    GLCall(unsigned int location =
               glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!"
                  << std::endl;
    } else {
        m_UniformLocationCache[ name ] = location;
    }
    return location;
}
} // namespace oogl