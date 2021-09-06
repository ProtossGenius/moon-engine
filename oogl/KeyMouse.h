#pragma once
#include <memory>
#include "smgame/nil.h"

namespace oogl {
	class KeyMouseItf {
	public:
		KeyMouseItf():m_MousePosX(0), m_MousePosY(0){}
	public:
		virtual void MouseButton(int button, int action, int mods) = 0;
		virtual void KeyBoards(int key, int scancode, int action, int mode) = 0;
		virtual void MouseScroll(double offset) = 0;
		virtual void Update() = 0;
	public:
		virtual void CursorPosition(double x, double y) { m_MousePosX = x; m_MousePosY = y; }

		double MousePosX() const { return m_MousePosX; }
		double MousePosY() const{ return m_MousePosY; }
	private:
		double m_MousePosX;
		double m_MousePosY;
	};

}

namespace smgame {
	template <> std::shared_ptr<oogl::KeyMouseItf> nil<oogl::KeyMouseItf>();
}
