#include "TestCamera.h"
#include "imgui/imgui.h"
#include "oogl/KeyMouse.h"
#include "oogl/Renderer.h"
namespace test {
using namespace oogl;

class KeyMouse : public KeyMouseItf {};

TestCamera::TestCamera(std::shared_ptr<Window> window)
    : Test(window)
    , m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f} {}
TestCamera::~TestCamera() {}
void TestCamera::OnUpdate(float deltaTime) {}
void TestCamera::OnRender() {
    GLCall(glClearColor(m_ClearColor[ 0 ], m_ClearColor[ 1 ], m_ClearColor[ 2 ],
                        m_ClearColor[ 3 ]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
void TestCamera::OnImGuiRender() {
    ImGui::ColorEdit4("Clear Color", m_ClearColor);
}
} // namespace test