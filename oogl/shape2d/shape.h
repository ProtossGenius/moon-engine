#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "oogl/IndexBuffer.h"
#include "oogl/Renderer.h"
#include "oogl/VertexArray.h"
#include "oogl/VertexBuffer.h"
#include "vec2d.h"
#include <memory>

namespace oogl {
class Window;
class Texture;
class Shader;

namespace shape2d {
class DrawUnit {
  public:
    DrawUnit()
        : m_translation(0, 0, 0)
        , m_rotation(0.0f)
        , m_scale(1.0f, 1.0f, 1.0f)
        , m_transparency(1.0f) {}
    virtual ~DrawUnit() {}

  public:
    void setPosition(float x, float y) {
        m_translation.x = x;
        m_translation.y = y;
    }
    // rotation.
    void setRotationAngle(float angleZ) { m_rotation = angleZ; }
    // scale resize .
    void setScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); }
    virtual void    draw() = 0;
    const glm::vec3 getScale() const { return m_scale; }
    float           getRotationAngle() const { return m_rotation; }
    const glm::vec3 getTranslation() const { return m_translation; }
    const float     getTransparency() const { return m_transparency; }
    glm::vec3 *     getTranslationPtr() { return &m_translation; }
    glm::vec3 &     getTranslationRef() { return m_translation; }
    void            setTranslation(const glm::vec3 &translation) {
        m_translation = translation;
    }
    void setTransparency(float transparency) { m_transparency = transparency; }

  protected:
    glm::vec3 m_translation;
    float     m_rotation;
    glm::vec3 m_scale;
    float     m_transparency;
};

class Drawable {
  private:
    virtual void onDraw(const glm::vec3 &translation, float rotationZ,
                        const glm::vec3 &scale, float transparency = 1.0f) = 0;

  public:
    Drawable() {}
    virtual ~Drawable(){};
    void draw(const DrawUnit &da) {
        draw(da.getTranslation(), da.getRotationAngle(), da.getScale(),
             da.getTransparency());
    }
    void draw(const glm::vec3 &translation, float rotation,
              const glm::vec3 &scale, float transparency) {
        onDraw(translation, rotation, scale, transparency);
    }
};

} // namespace shape2d

} // namespace oogl
