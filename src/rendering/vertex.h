#pragma once

#include <ce_math.h>

using namespace glm;

namespace ce {
	struct Vertex { // TODO: just remove this class entirely, vertexes don't and shouldn't work like this
		vec3 position;
		vec4 color;
		vec2 texCoord;
	};
}
