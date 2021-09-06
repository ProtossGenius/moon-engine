#pragma once

#include "smgame/unit_type.h"
#include <string>
#include <iostream>
#include <fstream>
namespace smgame{
	class RandomFile {
	public:
		RandomFile(const std::string& str):m_cur() {
			m_fs.open(str, std::ios::in | std::ios::out | std::ios::binary);
		}
		~RandomFile() { m_fs.close(); }
		UNCOPYABLE(RandomFile);
	public:
		
		std::fstream& seekg(std::fstream::pos_type start) {
			m_fs.seekg(start);
			return m_fs;
		}

	private:
		std::fstream m_fs;
		size_t m_cur;
	};
}