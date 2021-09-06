#pragma once

#include "Test.h"

#include <memory>

#include "oogl/VertexBuffer.h"
#include "oogl/VertexBufferLayout.h"
#include "oogl/Texture.h"
#include "oogl/shape2d/rectangle.h"
#include "oogl/shape2d/triangle.h"

namespace test {
	using namespace oogl;
	class TestTexture2D : public Test {
	public:
		TestTexture2D(std::shared_ptr<Window> window);
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		shape2d::rect4draw rect;
		shape2d::triangle_unit tri;
	};
}
