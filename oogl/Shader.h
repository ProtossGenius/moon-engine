#pragma once
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>
namespace oogl {
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FregmentSource;
};

class Shader {
  private:
    unsigned int                         m_RendererID;
    std::string                          m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

  public:
    Shader(const std::string filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform4f(const std::string &name, float v0, float v1, float v2,
                      float v3);
    void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform1i(const std::string &name, int value);

  private:
    ShaderProgramSource ParseShader(const std::string &filePath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader,
                              const std::string &fregmentShader);

    int GetUniformLocation(const std::string &name);
};
} // namespace oogl