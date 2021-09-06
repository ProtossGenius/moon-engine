#pragma once
#include <memory>
namespace smgame {
	// it should be always safe.
	template <typename Type>
	inline std::shared_ptr<Type> nil() {
		static std::shared_ptr<Type> instance(new Type());
		return instance; 
	}
}