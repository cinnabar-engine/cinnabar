#pragma once

#include <glm/glm.hpp>

namespace ce {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv = glm::vec2(0.0f, 0.0f);
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};
}
