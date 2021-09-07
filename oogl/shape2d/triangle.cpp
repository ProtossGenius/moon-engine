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
float        positions[ 12 ];
unsigned int triangle4draw::indices[] = {0, 1, 2};
void triangle4draw::onDraw(const glm::vec3 &translation, float rotationZ,
                           const glm::vec3 &scale, float transparency) {
    getShader().SetUniform1f("c_Transparency", transparency);
    getTexture().Bind();
    auto      envScale = getWindow().getScale();
    glm::mat4 model    = glm::translate(
        glm::mat4(1.0f), {translation.x * envScale.x,
                          translation.y * envScale.y, translation.z});
    glm::mat4 mvp =
        getWindow().getDrawProj() * getWindow().getDrawView() * model;
    mvp =
        glm::rotate(mvp, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
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
                             const std::string &     texturePath,
                             const triangle &showPos, const triangle &loadPos)
    : m_VAO() {
    auto texture = getTextureMgr().get(texturePath);
    init(win, texture, showPos, loadPos);
}

void triangle4draw::setShowPos(const triangle &showPos) {
    positions[ 0 ]  = showPos.p1.x;
    positions[ 1 ]  = showPos.p1.y;
    positions[ 2 ]  = m_loadPos.p1.x;
    positions[ 3 ]  = m_loadPos.p1.y;
    positions[ 4 ]  = showPos.p2.x;
    positions[ 5 ]  = showPos.p2.y;
    positions[ 6 ]  = m_loadPos.p2.x;
    positions[ 7 ]  = m_loadPos.p2.y;
    positions[ 8 ]  = showPos.p3.x;
    positions[ 9 ]  = showPos.p3.y;
    positions[ 10 ] = m_loadPos.p3.x;
    positions[ 11 ] = m_loadPos.p3.y;

    this->setVertexBuffer(
        std::make_shared<VertexBuffer>(positions, 4 * 3 * sizeof(float)));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    getVAO().AddBuffer(getVertexBuffer(), layout);
}

void triangle4draw::init(std::shared_ptr<Window>  win,
                         std::shared_ptr<Texture> texture,
                         const triangle &showPos, const triangle &loadPos) {
    m_loadPos = loadPos;
    this->setWindow(win);
    this->setTexture(texture);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    this->setShader(getShaderMgr().get("res/shaders/Basic.shader"));

    setShowPos(showPos);

    setIndexBuffer(std::make_shared<IndexBuffer>(indices, 6));

    getShader().Bind();
    getShader().SetUniform1i("u_Texture", 0);
}
} // namespace shape2d
} // namespace oogl