#include "sample_world_map2d.h"
#include "attribs/TerrainAttrib.h"
#include "smgame/errors.h"
#include "smgame/event.h"
#include "smgame/unit_type.h"
#include "userdef.h"
#include <iostream>
#include <memory>

namespace smgame_sample {
namespace x2d {
Terrain::Terrain()
    : Unit(0, 0, std::shared_ptr<AttributesItf>(createTerrainAttribute())) {}

ActionStatus Terrain::action_status() {
    return getAttributes()->getAttrib<TerrainAttribStatus>();
}

void Terrain::setIndex(WorldMap *map, int index) {
    getAttributes()->whenChange(
        [ map, index ](AttributesItf *itf) { map->onTerrainChange(index); });
}

WorldMap::WorldMap(Point pointZero, size_t cols, size_t lines)
    : world_itf({pointZero,
                 {static_cast<float>(cols * TerrainWidth()),
                  static_cast<float>(lines * TerrainHeight())}})
    , m_terrains(nullptr)
    , m_columns(cols)
    , m_lines(lines)
    , m_startUID(AllocTerrainUids(cols * lines)) {
    if (0 == cols) {
        throw SMGAME_ERROR("width shouldn't be zero");
    }
    if (0 == lines) {
        throw SMGAME_ERROR("height shouldn't be zero");
    }
    size_t size = cols * lines;
    m_terrains  = new Terrain[ size ];
    for (int i = 0; i < size; ++i) {
        m_terrains[ i ].setIndex(this, i);
    }
}
void WorldMap::areaDo(const std::list<std::shared_ptr<AreaEvent>> &events) {
    for (auto &e : events) {
        rangeInArea(e->area(), [ &e ](Terrain &t, const Rectangle &rect) {
            e->Act(t, rect);
        });
    }
}

void WorldMap::rangeInArea(
    const x2d::Rectangle &                                area,
    std::function<void(Terrain &, const Rectangle &rect)> act) {
    if (!Impact(this->area(), area)) {
        return;
    }
    Rectangle suitArea = area.suit(this->area());
    size_t    startX   = static_cast<size_t>(
               (suitArea.getZeroPoint().x - this->area().getZeroPoint().x) /
               TerrainWidth()),
           startY = static_cast<size_t>(
               (suitArea.getZeroPoint().y - this->area().getZeroPoint().y) /
               TerrainHeight()),
           endX = static_cast<size_t>(suitArea.getFlagPoint().x -
                                      this->area().getZeroPoint().x) /
                  TerrainWidth(),
           endY = static_cast<size_t>(suitArea.getFlagPoint().y -
                                      this->area().getZeroPoint().y) /
                  TerrainHeight();
    for (size_t x = startX; x < endX; ++x) {
        for (size_t y = startY; y < endY; ++y) {
            Rectangle terrainArea(
                {static_cast<smgame::LengthUnit>(x * TerrainWidth()),
                 static_cast<smgame::LengthUnit>(y * TerrainHeight())},
                {static_cast<smgame::LengthUnit>((x + 1) * TerrainWidth()),
                 static_cast<smgame::LengthUnit>((y + 1) * TerrainHeight())});
            act(terrain(x, y), terrainArea.suit(area));
        }
    }
}

void WorldMap::userEvent(const UnitID                             uid,
                         const std::list<std::shared_ptr<Event>> &events) {
    auto endUid =
        static_cast<UnitID>(terrain(0, 0).uid() + m_columns * m_lines);
    if (uid < m_startUID || uid > endUid) {
        std::cerr << ERROR_INFO("uid out of range, uid = " +
                                std::to_string(uid) + ", Map's startUid = " +
                                std::to_string(terrain(0, 0).uid()) +
                                ", Map's end Uid = " + std::to_string(endUid))
                  << std::endl;

        return;
    }

    auto &target = m_terrains[ uid - m_startUID ];

    for (auto e : events) {
        e->Act(target);
    }
}

Terrain &WorldMap::terrain(size_t x, size_t y) {
    if (x > m_columns)
        throw SMGAME_ERROR("x out of range, x = " + std::to_string(x) +
                           ", Map width = " + std::to_string(m_columns));
    if (y > m_lines)
        throw SMGAME_ERROR("y out of range, y = " + std::to_string(y) +
                           ", Map height = " + std::to_string(m_lines));
    return m_terrains[ x + y * m_columns ];
}

} // namespace x2d
} // namespace smgame_sample
