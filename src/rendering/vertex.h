#pragma once

#include <ce_math.h>

namespace ce {
	struct Vertex { // TODO: we need a better mesh system, probably just store the raw buffers instead of constantly converting
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv = glm::vec2(0.0f, 0.0f);
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};
}
