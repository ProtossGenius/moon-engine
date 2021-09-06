#pragma once
// Product by autocode, you shouldn't change it.
// Author : ProtossGenius
// tools path: cmd/attribs/attribs.go

#include "smgame/attributes_itf.h"
#include "smgame/sample/sample_attributes.h"

namespace smgame_sample {
	using namespace smgame;
	enum {AttribTypeTerrain = 0};

	enum {AttribTerrainInt32Nums = 2};

	// TerrainAttribHp .
	struct TerrainAttribHp{
		typedef Int32Attrib Trait;
		enum { AttribID = 0 };
		enum { AttribType = AttribTypeTerrain };
	};

	// TerrainAttribStatus  terrain's status.
	struct TerrainAttribStatus{
		typedef Int32Attrib Trait;
		enum { AttribID = 1 };
		enum { AttribType = AttribTypeTerrain };
	};

	enum {AttribTerrainInt64Nums = 0};

	enum {AttribTerrainFloatNums = 0};

	enum {AttribTerrainDoubleNums = 0};

	enum {AttribTerrainStringNums = 0};

	inline AttributesItf* createTerrainAttribute() {
		return new Attribute(AttribTypeTerrain, AttribTerrainFloatNums, AttribTerrainDoubleNums, AttribTerrainInt32Nums, 
			AttribTerrainInt64Nums, AttribTerrainStringNums);
	}
} // namespace smgame_sample
