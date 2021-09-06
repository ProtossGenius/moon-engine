// It's Mine userdef. TODO: you should change it.
#include "userdef.h"
#include "sample_attributes.h"
namespace smgame_sample {
	size_t TerrainWidth()
	{
		return size_t(100);
	}

	size_t TerrainHeight()
	{
		return size_t(100);
	}

	UnitType AllocTerrainUids(size_t num)
	{
		return 0;
	}


	void AttribParseMsg(smgame_sample::Attribute& a, const std::string&) {
	}

	std::string AttribAsMessage(const smgame_sample::Attribute&) {
		return "";
	}
}
