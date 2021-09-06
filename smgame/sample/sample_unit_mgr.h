#pragma once
#include "smgame/unit_type.h"
#include <memory>
#include <functional>
#include <list>
#include <smgame/space/srectangle.h>


namespace smgame_sample {
	using namespace smgame;
	typedef std::list<std::shared_ptr<Unit>> UnitList;
	typedef std::function<void(UnitList&, UnitList::iterator)> UnitMgrAct;
	typedef std::function<void(const Unit&)> ConstUnitAct;
	namespace x2d {
		class SubMgr;

		class UnitMgr {
		public:
			UnitMgr(const smgame::x2d::Rectangle& area, LengthUnit minSize);
			UNCOPYABLE(UnitMgr);
			void rangeUnit(const smgame::x2d::Rectangle& area, UnitMgrAct act) ;
			void rangeUnit(const smgame::x2d::Rectangle& area, ConstUnitAct act) const;
			const smgame::x2d::Rectangle& area() const{ return m_area; }
		private:
			std::unique_ptr<SubMgr> m_subMgr;
			std::list<std::shared_ptr<Unit> > m_units;
			smgame::x2d::Rectangle m_area;
		};

		class SubMgr {
		public:
			SubMgr(std::list<UnitMgr*>&& subMgrs):m_SubMgrs(subMgrs){}

			void rangeUnit(const smgame::x2d::Rectangle& area, UnitMgrAct act) ;
			void rangeUnit(const smgame::x2d::Rectangle& area, ConstUnitAct act) const;
			~SubMgr();
		private:
			std::list<UnitMgr*> m_SubMgrs;
		};
	}

}