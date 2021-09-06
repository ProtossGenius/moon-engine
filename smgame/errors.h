#pragma once
#include <string>
#include <stdexcept>

#define ERROR_INFO(info) std::string(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + __FUNCTION__ + "(...)\n" \
	+ info)

#define SMGAME_ERROR(info) std::runtime_error(ERROR_INFO(info))
