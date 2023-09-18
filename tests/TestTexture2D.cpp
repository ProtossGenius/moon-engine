#include "TestTexture2D.h"
#include "oogl/Managers.h"
#include "oogl/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace test {
using namespace oogl;
TestTexture2D::TestTexture2D(std::shared_ptr<Window> window)
    : Test(window)
    , rect(window, "res/textures/ChernoLogo.png", {200, 200})
    , tri(window, "res/textures/text.jpg",
          {{0.0f, 0.0f}, {100.0f, 0.0f}, {100.0f, 100.0f}},
          {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}) {
    tri.setPosition(200, 200);
    rect.setPosition(200, 200);
}
TestTexture2D::~TestTexture2D() {}
void TestTexture2D::OnUpdate(float deltaTime) {
    static int   len        = 20;
    static int   tow        = 10;
    static float rangle     = 0;
    static float tow_rangle = 2;
    rangle += tow_rangle;
    len += tow;
    if (len > 300 || len < 20) tow = -tow;
    // rect.setSize(len, len);
    //    rect.setRotationAngle({rangle, -rangle, rangle});
    //   tri.setRotationAngle({rangle, 0, 0});
    tri.setTransparency(static_cast<float>(len) / 300.f);
}
void TestTexture2D::OnRender() {
    tri.draw();
    rect.draw();
}
void TestTexture2D::OnImGuiRender() {
    ImGui::SliderFloat3(
        "Translation A", &rect.getTranslationRef().x, 0.0f,
        960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat3(
        "Translation B", &tri.getTranslationRef().x, 0.0f,
        960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    // int i = 100;
    // while (i--) {
    ImGui::ImageButton((void *) (unsigned long) oogl::getTextureMgr()
                           .get("res/textures/text.jpg")
                           ->ID(),
                       {50, 50});
    //}
}
} // namespace test
