#pragma once
// Product by autocode, you shouldn't change it.
// Author : ProtossGenius
// tools path: cmd/attribs/attribs.go

#include "sample_attributes.h"
#include "smgame/attributes_itf.h"

namespace smgame_sample {
using namespace smgame;
enum { AttribTypeUnit = 0 };

enum { AttribUnitInt32Nums = 2 };

// UnitAttribHp .
struct UnitAttribHp {
    typedef Int32Attrib Trait;
    enum { AttribID = 0 };
    enum { AttribType = AttribTypeUnit };
};

// UnitAttribStatus .
struct UnitAttribStatus {
    typedef Int32Attrib Trait;
    enum { AttribID = 1 };
    enum { AttribType = AttribTypeUnit };
};

enum { AttribUnitInt64Nums = 0 };

enum { AttribUnitFloatNums = 0 };

enum { AttribUnitDoubleNums = 0 };

enum { AttribUnitStringNums = 0 };

inline AttributesItf *createUnitAttribute() {
    return new Attribute(AttribTypeUnit, AttribUnitFloatNums,
                         AttribUnitDoubleNums, AttribUnitInt32Nums,
                         AttribUnitInt64Nums, AttribUnitStringNums);
}
} // namespace smgame_sample