#include "sample_unit_mgr.h"
#include <smgame/unit.h>
namespace smgame_sample {
namespace x2d {
UnitMgr::UnitMgr(const smgame::x2d::Rectangle &area, LengthUnit minSize)
    : m_area(area)
    , m_subMgr(nullptr) {
    LengthUnit width = area.getWidth(), height = area.getHeight(),
               midWidth = width / 2, midHeight = height / 2;
    const auto &         fp = area.getFlagPoint(), &zp = area.getZeroPoint();
    std::list<UnitMgr *> subMgrs;
    if (width <= minSize && height <= minSize) {
        return;
    }

    if (width <= minSize) {
        subMgrs.emplace_back(
            new UnitMgr({zp, {fp.x, fp.y - midHeight}}, minSize));
        subMgrs.emplace_back(
            new UnitMgr({{zp.x, zp.y + midHeight}, fp}, minSize));
    } else if (height <= minSize) {
        subMgrs.emplace_back(
            new UnitMgr({zp, {fp.x - midWidth, fp.y}}, minSize));
        subMgrs.emplace_back(
            new UnitMgr({{zp.x + midWidth, zp.y}, fp}, minSize));
    } else {
        subMgrs.emplace_back(
            new UnitMgr({zp, {zp.x + midWidth, zp.y + midHeight}}, minSize));
        subMgrs.emplace_back(new UnitMgr(
            {{zp.x, zp.y + midHeight}, {zp.x + midWidth, fp.y}}, minSize));
        subMgrs.emplace_back(new UnitMgr(
            {{zp.x + midWidth, zp.y}, {fp.x, zp.y + midHeight}}, minSize));
        subMgrs.emplace_back(
            new UnitMgr({{zp.x + midWidth, zp.y + midHeight}, fp}, minSize));
    }
    m_subMgr.reset(new SubMgr(std::move(subMgrs)));
}
void UnitMgr::rangeUnit(const smgame::x2d::Rectangle &area, UnitMgrAct act) {
    if (!Impact(this->m_area, area)) {
        return;
    }

    if (this->m_subMgr != nullptr) {
        m_subMgr->rangeUnit(area, act);
        return;
    }

    for (auto it = m_units.begin(); it != m_units.end();) {
        act(m_units, it++);
    }
}

void UnitMgr::rangeUnit(const smgame::x2d::Rectangle &area,
                        ConstUnitAct                  act) const {
    if (!Impact(this->m_area, area)) {
        return;
    }

    if (this->m_subMgr != nullptr) {
        m_subMgr->rangeUnit(area, act);
        return;
    }

    for (auto &it : m_units) {
        act(*it);
    }
}

void SubMgr::rangeUnit(const smgame::x2d::Rectangle &area, UnitMgrAct act) {
    for (auto &mgr : m_SubMgrs) {
        if (Impact(mgr->area(), area)) mgr->rangeUnit(area, act);
    }
}

void SubMgr::rangeUnit(const smgame::x2d::Rectangle &area,
                       ConstUnitAct                  act) const {
    for (auto &mgr : m_SubMgrs) {
        if (Impact(mgr->area(), area)) mgr->rangeUnit(area, act);
    }
}

SubMgr::~SubMgr() {
    for (auto it : m_SubMgrs) {
        delete it;
    }
}

} // namespace x2d
} // namespace smgame_sample