#include "scircle.h"
#include "smath.h"
#include "srectangle.h"
namespace smgame {
	namespace x2d {

		bool Circle::Impact(const CoordinateLine& line)const
		{
			if (distance(Center, line.startPoint()) < Redis || distance(Center, { line.Pos, line.Start }) < Redis) {
				return true;
			}

			if (line.Type == CoordinateLineType::ParrallelX) {
				return in_range(Center.x, line.Start, line.End) && std::abs(line.Pos - Center.y) < Redis;
			}

			return in_range(Center.y, line.Start, line.End) && std::abs(line.Pos - Center.x) < Redis;
		}

		bool Impact(const Rectangle& r, const Circle& c)
		{
			if (r.Impact(c.Center))return true;
			bool isImpact = false;
			r.rangeCoorrdinateLine([&c, &isImpact](const CoordinateLine& l) {if (c.Impact(l))isImpact = true; });
			return isImpact;
		}

	}
}