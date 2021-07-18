#pragma once

#include <ce_math.h>


namespace ce {
	struct Vertex { // TODO: just remove this class entirely, vertexes don't and shouldn't work like this
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};
}
