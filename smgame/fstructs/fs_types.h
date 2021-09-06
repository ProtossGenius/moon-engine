#pragma once
#include "fs_file.h"
#include <iostream>
#include <string>
#include "smgame/errors.h"
#include "smgame/nil.h"

namespace smgame{
	template<typename Type>
	class FsType {
	public:
		FsType() : m_pos(new int(0)){}
		FsType(int* pos):m_pos(pos){}
	public:
		const Type& getVal();
	private:
		int* m_pos;

	};
}