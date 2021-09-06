#pragma once
#include "space_base.h"
#include <functional>
namespace smgame {

	namespace x2d {
		/*
		*   ^
		*	|--------    FlagPoint
			|        |
			|        |
		 ---|------------>
			|ZeroPoint

		*/
		class Rectangle {
		private:
			Point m_ZeroPoint, m_FlagPoint;
		public:
			Rectangle(const Point& p1, const Point& p2);
			const Point& getZeroPoint() const { return m_ZeroPoint; }
			const Point& getFlagPoint() const { return m_FlagPoint; }
			const LengthUnit getWidth() const { return m_FlagPoint.x; }
			const LengthUnit getHeight() const { return m_FlagPoint.y; }
			// suit rhs, let it in rhs.
			// result: rhs.ZeroPoint <= result.ZeroPoint <= result.FlagPoint <= rhs.FlagPoint.
			Rectangle suit(const Rectangle& rhs) const;

			void rangePoint(std::function<void(const Point&)> act) const;
			void rangeCoorrdinateLine(std::function<void(const CoordinateLine& )> act)const;

			bool Impact(const Point& p) const;
			bool Impact(const CoordinateLine& line)const;
		public:
			static Rectangle Zero;
		};
		
		bool Impact(const Rectangle& r1, const Rectangle& r2);

	}
}