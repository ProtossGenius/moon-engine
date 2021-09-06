#pragma once
#define oogl_pair_class(name, first, second) \
	struct name { \
	name():first(0.0f), second(0.0f){}\
	name(float first, float second) :first(first), second(second){} \
		float first, second; \
	};

namespace oogl {
	namespace shape2d {
		oogl_pair_class(Position, x, y);
		oogl_pair_class(Size, width, height);
	}
}