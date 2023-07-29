#pragma once
#include "shape.h"
#include <string>
namespace oogl {
class Window;

namespace shape2d {
class triangle {
  public:
    triangle() {}
    triangle(Position p1, Position p2, Position p3)
        : p1(p1)
        , p2(p2)
        , p3(p3) {}
    ~triangle() {}
    Position p1, p2, p3;
};

class triangle4draw : public Drawable {
  public:
    triangle4draw(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture,
                  const triangle &showPos, const triangle &loadPos);
    triangle4draw(std::shared_ptr<Window> win, const std::string &texturePath,
                  const triangle &showPos, const triangle &loadPos);

  public:
    void setShowPos(const triangle &showPos);

  private:
    void onDraw(const glm::vec3 &translation, glm::vec3 rotationZ,
                const glm::vec3 &scale, float transparency) override;
    void init(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture,
              const triangle &showPos, const triangle &loadPos);

  private:
    static unsigned int indices[];
    triangle            m_loadPos;

  protected:
    void    setWindow(const std::shared_ptr<Window> &win) { m_win = win; }
    Window &getWindow() { return *m_win; }
    void    setTexture(const std::shared_ptr<Texture> &texture) {
           m_texture = texture;
    }
    std::shared_ptr<Window> &window() { return m_win; }
    Texture                 &getTexture() { return *m_texture; }
    void setShader(const std::shared_ptr<Shader> &shader) { m_shader = shader; }
    Shader &getShader() { return *m_shader; }
    void    setVertexBuffer(const std::shared_ptr<VertexBuffer> &vbuffer) {
           m_VertexBuffer = vbuffer;
    }
    VertexBuffer &getVertexBuffer() { return *m_VertexBuffer; }
    VertexArray  &getVAO() { return m_VAO; }
    IndexBuffer  &getIndexBuffer() { return *m_IndexBuffer; }
    void          setIndexBuffer(std::shared_ptr<IndexBuffer> ibuffer) {
                 m_IndexBuffer = ibuffer;
    }
    Renderer &getRender() { return Renderer::Instance; }

  private:
    std::shared_ptr<Window>       m_win;
    std::shared_ptr<Texture>      m_texture;
    std::shared_ptr<Shader>       m_shader;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;

    VertexArray                  m_VAO;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

class triangle_unit : public triangle4draw, public DrawUnit {
  public:
    triangle_unit(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture,
                  const triangle &showPos, const triangle &loadPos)
        : triangle4draw(win, texture, showPos, loadPos)
        , DrawUnit() {}
    triangle_unit(std::shared_ptr<Window> win, const std::string &texturePath,
                  const triangle &showPos, const triangle &loadPos)
        : triangle4draw(win, texturePath, showPos, loadPos)
        , DrawUnit() {}

  public:
    void draw() override { triangle4draw::draw(*this); }
};
} // namespace shape2d

} // namespace oogl
