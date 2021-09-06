#pragma once
#include "oogl/shape2d/shape.h"
#include "oogl/shape2d/rectangle.h"
#include <vector>
#include <ctime>

namespace oogl {
	namespace shape2d {
		class animation :public DrawUnit{
		public:
			typedef std::vector<rect4draw> Frames;
		public:
			animation(const Frames& frames, const clock_t interval):
				m_frames(frames), m_index(0), m_interval(interval), m_next(0){}
		public:
			void draw()override;
		private:
			Frames m_frames;
			size_t m_index;
			const clock_t m_interval;
			clock_t m_next; // next draw time.
		};
		
	}
}