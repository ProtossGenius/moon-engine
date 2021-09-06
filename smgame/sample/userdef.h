#pragma once
#include <ctype.h>
#include "smgame/unit_type.h"
/*
*  Only function-interface in here, uesr should include this file and define the functions.
*/
namespace smgame_sample {
	using namespace smgame;
	class Attribute;
	// TerrainWidth get Terrain's Width, for draw and calc.
	size_t TerrainWidth();

	// TerrainHeight get Terrain's Height, for draw and calc.
	size_t TerrainHeight();
	UnitType AllocTerrainUids(size_t num);

	void AttribParseMsg(smgame_sample::Attribute&, const std::string&);
	std::string AttribAsMessage(const smgame_sample::Attribute&);
}
