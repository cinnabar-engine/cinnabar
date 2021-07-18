#pragma once

#include <ce_math.h>

namespace ce {
	struct Vertex { // TODO: we need a better mesh system, probably just store the raw buffers instead of constantly converting
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};
}
