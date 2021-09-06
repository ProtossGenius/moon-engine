#pragma once
#include "unit_type.h"
#include <list>
#include <memory>
#include "smgame/space/srectangle.h"
namespace smgame {
	namespace x2d {
		//2d game's world.
		class world_itf {
		private:
			Rectangle m_area;

		public:
			world_itf(const Rectangle& area) :m_area(area) {}
		public:
			virtual void areaDo(const std::list<std::shared_ptr<AreaEvent>>&) = 0;
			virtual void userEvent(const UnitID uid, const std::list<std::shared_ptr<Event> >& events) = 0;
		public:
			void setArea(Rectangle area) { m_area = area; }
			const Rectangle& area() const { return m_area; }
		public:
			virtual ~world_itf() {}
		};
	}

	namespace x3d {

	}

}