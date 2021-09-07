#pragma once
#include "attributes_itf.h"
#include "smgame/space/spacefwd.h"
#include "unit_type.h"
#include <memory>
namespace smgame {
// Unit .
class Unit {
  public:
    Unit(UnitID uid, UnitType type, std::shared_ptr<AttributesItf> attrs)
        : m_uid(uid)
        , m_type(type)
        , m_pos(0, 0)
        , m_attr(attrs) {}

  public:
    UnitID          uid() const { return m_uid; }
    UnitType        type() const { return m_type; }
    const Position &getPosition() const { return m_pos; }
    void            setPosition(LengthUnit x, LengthUnit y) { m_pos = {x, y}; }
    void            setPosition(const Position &p) { m_pos = p; }
    std::shared_ptr<AttributesItf> getAttributes() { return m_attr; }

  public: // virtual
    virtual ActionStatus action_status()                    = 0;
    virtual bool         Impact(const x2d::Rectangle &area) = 0;

    virtual ~Unit() {}

  private:
    UnitID                         m_uid;
    UnitType                       m_type;
    Position                       m_pos;
    std::shared_ptr<AttributesItf> m_attr;
};

} // namespace smgame