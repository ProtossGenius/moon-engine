#pragma once
#include <math.h>
#include <algorithm>
namespace smgame {

	template<typename Type>
	inline Type max(Type a, Type b) { return a > b ? a : b; }

	template<typename Type>
	inline Type min(Type a, Type b) { return a < b ? a : b; }

	template<typename Type>
	inline bool in_range(Type n, Type start, Type end) {
		using namespace std;
		if (start > end) { swap(start, end); }
		return n >= start && n <= end;
	}

	template<typename Type>
	inline bool out_range(Type n, Type start, Type end) {
		return !in_range(n, start, end);
	}

	template<typename Type>
	inline bool impact(Type startA, Type endA, Type startB, Type endB) {
		return in_range(startA, startB, endB) || in_range(endA, startB, endB) ||
			in_range(startB, startA, endA) || in_range(endB, startA, endA);
	}

	template <typename Type>
	inline Type square(Type t) {
		return t * t;
	}
}