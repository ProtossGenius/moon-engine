#pragma once
#include "space/space_base.h"
#include <string>

#define UNCOPYABLE(className)                                                  \
    className(const className &) = delete;                                     \
    className &operator=(const className &) = delete

namespace smgame {
using UnitType     = int32_t;
using UnitID       = int64_t;
using ActionStatus = int16_t;

// forward define;
class Unit;
class Event;
namespace x2d {
class AreaEvent;
}
} // namespace smgame