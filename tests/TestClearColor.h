#pragma once

#include "Test.h"


namespace test {
	class TestClearColor : public Test {
	public:
		TestClearColor(std::shared_ptr<oogl::Window> window);
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}
