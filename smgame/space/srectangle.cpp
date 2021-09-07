#include "srectangle.h"
#include "smath.h"
namespace smgame {
namespace x2d {
Rectangle::Rectangle(const Point &p1, const Point &p2)
    : m_ZeroPoint(min(p1.x, p2.x), max(p1.y, p2.y))
    , m_FlagPoint(max(p1.x, p2.x), min(p1.y, p2.y)) {}

Rectangle Rectangle::suit(const Rectangle &rhs) const {
    return Rectangle(
        {min(max(m_ZeroPoint.x, rhs.m_ZeroPoint.x), rhs.m_FlagPoint.x),
         min(max(m_ZeroPoint.y, m_ZeroPoint.y), rhs.m_FlagPoint.y)},
        {max(min(m_FlagPoint.x, rhs.m_FlagPoint.x), m_ZeroPoint.x),
         max(min(m_FlagPoint.y, rhs.m_FlagPoint.y), m_ZeroPoint.y)});
}
Rectangle Rectangle::Zero({0, 0}, {0, 0});
void      Rectangle::rangePoint(std::function<void(const Point &)> act) const {
    act(m_ZeroPoint);
    act({m_ZeroPoint.x, m_FlagPoint.y});
    act(m_FlagPoint);
    act({m_FlagPoint.x, m_ZeroPoint.y});
}

void Rectangle::rangeCoorrdinateLine(
    std::function<void(const CoordinateLine &)> act) const {
    act({CoordinateLineType::ParrallelX, m_ZeroPoint.y, m_ZeroPoint.x,
         m_FlagPoint.x});
    act({CoordinateLineType::ParrallelY, m_ZeroPoint.x, m_ZeroPoint.y,
         m_FlagPoint.y});
    act({CoordinateLineType::ParrallelX, m_FlagPoint.y, m_ZeroPoint.x,
         m_FlagPoint.x});
    act({CoordinateLineType::ParrallelY, m_FlagPoint.x, m_ZeroPoint.y,
         m_FlagPoint.y});
}

bool Rectangle::Impact(const Point &p) const {
    return in_range(p.x, m_ZeroPoint.x, m_FlagPoint.x) &&
           in_range(p.y, m_FlagPoint.y, m_ZeroPoint.y);
}

bool Rectangle::Impact(const CoordinateLine &line) const {
    switch (line.Type) {
    case CoordinateLineType::ParrallelX:
        return in_range(line.Pos, m_ZeroPoint.x, m_FlagPoint.x) &&
               impact(m_ZeroPoint.y, m_FlagPoint.y, line.Start, line.End);

    case CoordinateLineType::ParrallelY:
        return in_range(line.Pos, m_ZeroPoint.y, m_FlagPoint.y) &&
               impact(m_ZeroPoint.x, m_FlagPoint.x, line.Start, line.End);
    default:
        return false;
    }
}

bool Impact(const Rectangle &r1, const Rectangle &r2) {
    bool isImpact = false;
    r1.rangeCoorrdinateLine([ &isImpact, &r2 ](const CoordinateLine &l) {
        if (r2.Impact(l)) isImpact = true;
    });
    if (isImpact) return true;
    r2.rangeCoorrdinateLine([ &isImpact, &r1 ](const CoordinateLine &l) {
        if (r1.Impact(l)) isImpact = true;
    });
    return isImpact;
}

} // namespace x2d
} // namespace smgame