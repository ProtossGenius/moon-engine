#pragma once

#include "space_base.h"
namespace smgame {
namespace x2d {
class Circle {
  public:
    Point      Center;
    LengthUnit Redis;

  public:
    bool Impact(const Point &p) const {
        return ::smgame::distance(Center, p) < Redis;
    }
    bool Impact(const CoordinateLine &line) const;
    bool Impact(const Circle &c) const {
        return ::smgame::distance(Center, c.Center) < (Redis + c.Redis);
    }
};

bool Impact(const Circle &c1, const Circle &c2) { return c1.Impact(c2); }

class Rectangle;

bool        Impact(const Rectangle &r, const Circle &c);
inline bool Impact(const Circle &c, const Rectangle &r) { return Impact(r, c); }
} // namespace x2d
} // namespace smgame