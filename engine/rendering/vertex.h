#pragma once

#include <ce_math.h>

using namespace glm;

namespace ce {
	struct Vertex {
		vec3 position;
		vec4 color;
		vec2 texCoord;
	};
}