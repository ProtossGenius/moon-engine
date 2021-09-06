#include "TestClearColor.h"
#include "oogl/Renderer.h"

#include "imgui/imgui.h"

namespace test {
	using namespace oogl;
	TestClearColor::TestClearColor(std::shared_ptr<Window> window) :Test(window),m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
	{

	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}
	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}