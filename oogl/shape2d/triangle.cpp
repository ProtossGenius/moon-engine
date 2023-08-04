#include "triangle.h"
#include "glm/gtc/matrix_transform.hpp"
#include "oogl/Managers.h"
#include "oogl/Texture.h"
#include "oogl/VertexBufferLayout.h"
#include "oogl/Window.h"
#include <cmath>
#include <iostream>
using namespace std;
namespace oogl {
namespace shape2d {
unsigned int triangle4draw::indices[] = {0, 1, 2};
void triangle4draw::onDraw(const glm::vec3 &translation, glm::vec3 rotation,
                           const glm::vec3 &scale, float transparency) {
    getShader().SetUniform1f("c_Transparency", transparency);
    getTexture().Bind();
    auto      envScale = getWindow().getScale();
    glm::mat4 model =
        glm::translate(glm::mat4(1.0f),
                       {translation.x * envScale.x, translation.y * envScale.y,
                        translation.z * envScale.z});
    glm::mat4 mvp =
        getWindow().getDrawProj() * getWindow().getDrawView() * model;
    if (rotation.x != 0)
        mvp = glm::rotate(mvp, glm::radians(rotation.x),
                          glm::vec3(1.0f, 0.0f, 0.0f));
    if (rotation.y != 0)
        mvp = glm::rotate(mvp, glm::radians(rotation.y),
                          glm::vec3(0.0f, 1.0f, 0.0f));
    if (rotation.z != 0)
        mvp = glm::rotate(mvp, glm::radians(rotation.z),
                          glm::vec3(0.0f, 0.0f, 1.0f));
    mvp = glm::scale(mvp, envScale);
    mvp = glm::scale(mvp, scale);

    getShader().Bind();
    getShader().SetUniformMat4f("u_MVP", mvp);
    getRender().Draw(getVAO(), getIndexBuffer(), getShader());
}
triangle4draw::triangle4draw(std::shared_ptr<Window>  win,
                             std::shared_ptr<Texture> texture,
                             const triangle &showPos, const triangle &loadPos)
    : m_VAO() {
    init(win, texture, showPos, loadPos);
}
triangle4draw::triangle4draw(std::shared_ptr<Window> win,
                             const std::string      &texturePath,
                             const triangle &showPos, const triangle &loadPos)
    : m_VAO() {
    auto texture = getTextureMgr().get(texturePath);
    init(win, texture, showPos, loadPos);
}

void triangle4draw::setShowPos(const triangle &showPos) {
    float positions[ 12 ]{showPos.p1.x,   showPos.p1.y,   m_loadPos.p1.x,
                          m_loadPos.p1.y, showPos.p2.x,   showPos.p2.y,
                          m_loadPos.p2.x, m_loadPos.p2.y, showPos.p3.x,
                          showPos.p3.y,   m_loadPos.p3.x, m_loadPos.p3.y};

    this->setVertexBuffer(
        std::make_shared<VertexBuffer>(positions, 4 * 3 * sizeof(float)));
    VertexBufferLayout layout;
    layout.Push<float>(2); // per showPos use two float
    layout.Push<float>(2); // per loadPos use two float
    getVAO().AddBuffer(getVertexBuffer(), layout);
}

void triangle4draw::init(std::shared_ptr<Window>  win,
                         std::shared_ptr<Texture> texture,
                         const triangle &showPos, const triangle &loadPos) {
    m_loadPos = loadPos;
    this->setWindow(win);
    this->setTexture(texture);
    setShowPos(showPos);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    this->setShader(getShaderMgr().get("res/shaders/Basic.shader"));

    setIndexBuffer(std::make_shared<IndexBuffer>(indices, 3));

    getShader().Bind();
    getShader().SetUniform1i("u_Texture", 0);
}
} // namespace shape2d
} // namespace oogl