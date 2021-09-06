#include "rectangle.h"
#include "oogl/Window.h"
#include "oogl/Managers.h"
#include "oogl/Texture.h"
#include "oogl/VertexBufferLayout.h"
#include <iostream>
using namespace std;
namespace oogl {
	namespace shape2d {

		rectangle loadPos{ {0.0f, 0.0f}, {1.0f, 1.0f} };


		rect4draw::rect4draw(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture, const Size& size):
			m_leftUp(win, texture, { {0.0f, 0.0f}, {size.width, 0.0f}, {size.width, size.height} }, 
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_rightDown(win, texture, { {0.0f, 0.0f}, {0.0f, size.height}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.leftUp.x, loadPos.rightDown.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_size(size)
		{			
		}

		rect4draw::rect4draw(std::shared_ptr<Window> win, const std::string& texturePath, const Size& size) :
			m_leftUp(win, texturePath, { {0.0f, 0.0f}, {size.width, 0.0f}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_rightDown(win, texturePath, { {0.0f, 0.0f}, {0.0f, size.height}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.leftUp.x, loadPos.rightDown.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_size(size)
		{			
		}

		rect4draw::rect4draw(std::shared_ptr<Window> win, std::shared_ptr<Texture> texture, const Size& size, const rectangle& loadPos) :
			m_leftUp(win, texture, { {0.0f, 0.0f}, {size.width, 0.0f}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_rightDown(win, texture, { {0.0f, 0.0f}, {0.0f, size.height}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.leftUp.x, loadPos.rightDown.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_size(size)
		{			
		}

		rect4draw::rect4draw(std::shared_ptr<Window> win, const std::string& texturePath, const Size& size, const rectangle& loadPos) :
			m_leftUp(win, texturePath, { {0.0f, 0.0f}, {size.width, 0.0f}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.leftUp.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_rightDown(win, texturePath, { {0.0f, 0.0f}, {0.0f, size.height}, {size.width, size.height} },
				{ {loadPos.leftUp.x, loadPos.leftUp.y}, {loadPos.leftUp.x, loadPos.rightDown.y}, {loadPos.rightDown.x, loadPos.rightDown.y} }),
			m_size(size)
		{
		}

		void rect4draw::setSize(const Size& size)
		{
			setScale(size.width / m_size.width, size.height / m_size.height, 1);
		}

		void rect4draw::draw()
		{
			m_leftUp.draw(*this);
			m_rightDown.draw(*this);
		}

	}
}
