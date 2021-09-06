#pragma once
#include "triangle.h"
#include <string>
namespace oogl {
	class Window;

	namespace shape2d
	{
		class rectangle
		{
		public:
			rectangle() {}
			rectangle(Position leftUp, Position rightDown) :
				leftUp(leftUp), rightDown(rightDown) {}
			~rectangle() {}
			Position leftUp, rightDown;
		};
		class rect4draw : public DrawUnit
		{
		public:
			
			rect4draw(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture, const Size& size);
			rect4draw(std::shared_ptr<Window> win, const std::string& texturePath, const Size& size);

			rect4draw(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture, const Size& size, const rectangle& loadPos);
			rect4draw(std::shared_ptr<Window> win, const std::string& texturePath, const Size& size, const rectangle& loadPos);
		
			void setSize(const Size& size);
			void setSize(float width, float height) { setSize({ width, height }); }
		public:
			void draw() override ;
		private:
			triangle4draw m_leftUp;
			triangle4draw m_rightDown;
			Size m_size;
		};

	}
}
