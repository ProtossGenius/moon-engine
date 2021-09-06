#include "animation.h"
namespace oogl {
	namespace shape2d{
		void animation::draw()
		{
			auto now = clock();
			auto& current = m_frames[m_index];
			current.draw();
			if (m_next > now) {
				return;
			}

			m_next = now + m_interval;
			++m_index;
			if (m_index == m_frames.size())m_index = 0;
		}
	}
}