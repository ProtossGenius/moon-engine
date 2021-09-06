#pragma once
#include "smgame/world_itf.h"
#include "smgame/unit.h"
#include <vector>

namespace smgame_sample {
	namespace x2d {
		using namespace smgame;
		using namespace smgame::x2d;
		class WorldMap;
		// Maps's unit, it's size is 1*1;
		class Terrain : public Unit {
		public:
			Terrain();
		public:
			ActionStatus action_status() override;
			void setIndex(WorldMap* map, int index);
			virtual bool Impact(const x2d::Rectangle& area) override { return false; }
		private:
		};
   /*\ // Zero Point in leftDown
	*
	*  y / lines
	* 
	* 
	* -----------
	* 0 | 1 | 2 |  ...
0, 0* * * * * * * * * * *     x / cols
	* 
 	*/
		class WorldMap :public world_itf {
		public:
			WorldMap(Point pointZero, size_t cols, size_t lines);
			~WorldMap() { if (m_terrains) delete[] m_terrains; }
			friend class Terrain;
		public:
			void areaDo(const std::list<std::shared_ptr<AreaEvent>>& events) override;
			void rangeInArea(const x2d::Rectangle& area, std::function<void(Terrain&, const x2d::Rectangle&)> act);
			void userEvent(const UnitID uid, const std::list<std::shared_ptr<Event> >& events) override;
			// (0, 0) is leftDown;
			Terrain& terrain(size_t x, size_t y);
		public:
			size_t getWidth() const{ return m_columns; }
			size_t getHeight() const { return m_lines; }
		private:
			// getStartUID get terrain(0, 0)'s uid;
			UnitID getStartUID() const { return m_startUID; }
			virtual void onTerrainChange(int index) {}
		private:
			Terrain* m_terrains;
			size_t m_columns;
			size_t m_lines;
			UnitID m_startUID;
		};
	}
}