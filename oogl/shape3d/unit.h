#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "oogl/IndexBuffer.h"
#include "oogl/Renderer.h"
#include "oogl/VertexArray.h"
#include "oogl/VertexBuffer.h"
#include <memory>

namespace oogl {
class Window;
class Texture;
class Shader;

namespace s3d {
class Unit {
  public:
    Unit() {}
    virtual ~Unit() {}

  public:
    void setPosition(float x, float y, float z) { m_position = {x, y, z}; }
    // rotation.
    void setRotationAngle(glm::vec3 rotation) { m_rotation = rotation; }
    // scale resize .
    void setScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); }
    virtual void     draw() = 0;
    const glm::vec3  getScale() const { return m_scale; }
    const glm::vec3 &getRotationAngle() const { return m_rotation; }
    const glm::vec3 &getTranslation() const { return m_position; }
    const float      getTransparency() const { return m_transparency; }
    glm::vec3       *getTranslationPtr() { return &m_position; }
    glm::vec3       &getTranslationRef() { return m_position; }
    void             setTranslation(const glm::vec3 &translation) {
        m_position = translation;
    }
    void setTransparency(float transparency) { m_transparency = transparency; }

  public:
    virtual glm::mat4 getTransform(const glm::vec3 &envScale) = 0;

  private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    float     m_transparency;
    Unit     *parent = nullptr;
};

} // namespace s3d

} // namespace oogl
