#include "Test.h"
#include "imgui/imgui.h"
#include "oogl/Window.h"
namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer, std::shared_ptr<oogl::Window> window)
		:Test(window), m_currentTest(currentTestPointer)
	{
	}
	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_currentTest = test.second();
			}
		}
	}

}