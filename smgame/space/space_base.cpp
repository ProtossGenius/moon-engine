#include "space_base.h"
#include "smath.h"

namespace smgame {
LengthUnit distance(Point a, Point b) {
    return sqrt(square(a.x - b.x) + square(a.y - b.y) + square(a.z - b.z));
}

namespace x2d {
Point CoordinateLine::startPoint() const {
    if (Type == CoordinateLineType::ParrallelX) {
        return {Start, Pos};
    }

    return {Pos, Start};
}
Point CoordinateLine::endPoint() const {
    if (Type == CoordinateLineType::ParrallelX) {
        return {End, Pos};
    }

    return {Pos, End};
}
} // namespace x2d
} // namespace smgame
